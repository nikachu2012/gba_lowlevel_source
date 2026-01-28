import argparse
from PIL import Image

parser = argparse.ArgumentParser(description="画像をC言語ヘッダに変換します")
parser.add_argument("input", help="入力の画像ファイル", default="image.png")
parser.add_argument("label", help="変数名", default="image")

args = parser.parse_args()

img = Image.open(args.input)

img = img.convert("RGBA")
data = list(img.get_flattened_data())

print(f"#pragma once")

print(f"const int {args.label}DataWidth = {img.width};")
print(f"const int {args.label}DataHeight = {img.height};")

print(
  f"const unsigned short {args.label}Data[{img.width*img.height}] = {{")
print(f"    ", end="")

for d in range(len(data) - 1):
  r, g, b, a = data[d]
  val = ((b & 0xf8) >> 3) << 10 | ((g & 0xf8) >> 3) << 5 | (r & 0xf8) >> 3
  print(f"0x{val:02x}, ", end="")

r, g, b, a = data[-1]
val = ((b & 0xf8) >> 3) << 10 | ((g & 0xf8) >> 3) << 5 | (r & 0xf8) >> 3
print(f"0x{val:02x}")

print(f"}};")
