from math import ceil
from sys import exit
from typing import Final
from PIL import ImageFont
from PIL import Image
from PIL import ImageDraw
import argparse

# FONT_PATH: Final[str] = "./tools/genfont/ProggyClean.ttf"
# OUTPUT_PATH: Final[str] = "./tools/genfont/font.bin"
# CHAR_WIDTH: Final[int] = 7
# CHAR_HEIGHT: Final[int] = 13
# BYTE_PERLINE: Final[int] = ceil(CHAR_WIDTH / 8)  # WIDTHを表すのに必要なビット数

parser = argparse.ArgumentParser(
    description="ttf形式のフォントファイルから指定サイズのビットマップバイナリを作成します"
)
parser.add_argument("input", help="入力のttfファイル")
parser.add_argument("output", help="出力のttfファイル")
parser.add_argument("width", help="１文字の横幅")
parser.add_argument("height", help="１文字の縦幅")

args = parser.parse_args()

FONT_PATH: Final[str] = args.input
OUTPUT_PATH: Final[str] = args.output
CHAR_WIDTH: Final[int] = int(args.width)
CHAR_HEIGHT: Final[int] = int(args.height)
BYTE_PERLINE: Final[int] = ceil(CHAR_WIDTH / 8)  # WIDTHを表すのに必要なビット数

font = ImageFont.truetype(FONT_PATH, 16)


def getBitmap(char) -> list[int]:
    img = Image.new("L", (CHAR_WIDTH, CHAR_HEIGHT), 255)
    draw = ImageDraw.Draw(img)
    draw.text((0, 0), char[0], 0, font=font)
    draw = ImageDraw.Draw(img)

    return list(img.getdata())


def main():
    with open(OUTPUT_PATH, "wb") as f:

        for i in range(128):
            bitmap = getBitmap(chr(i))

            for y in range(CHAR_HEIGHT):
                temp: int = 0

                for x in range(CHAR_WIDTH):
                    if bitmap[CHAR_WIDTH * y + x] == 0:
                        temp |= 0b1 << (CHAR_WIDTH - x - 1)

                f.write(temp.to_bytes(length=BYTE_PERLINE, byteorder="big", signed=False))

    exit(0)


if __name__ == "__main__":
    main()
