
#define REG_DISPCNT (*(volatile unsigned short *)0x04000000)
#define VRAM ((volatile unsigned short *)0x06000000)

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 160

#define BG_MODE3 (3)
#define BG2_ON (1 << 10)

void initalizeDisplay() {
  // BGモード3, BG2を有効にする
  REG_DISPCNT = BG2_ON | BG_MODE3;

  // 白で塗りつぶす
  for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; i++) {
    VRAM[i] = 0x7fff;
  }
}

void drawPixel(int x, int y, unsigned short s) {
  VRAM[DISPLAY_WIDTH * y + x] = s;
}

const int char_A[8][7] = {
    {0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0},
    {0, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 1, 0},
};

int main(void) {
  initalizeDisplay();

  int x = 100, y = 100;

  // 文字の描画
  for (int dy = 0; dy < 8; dy++) {
    for (int dx = 0; dx < 7; dx++) {
      if (char_A[dy][dx] == 1) {
        drawPixel(x + dx, y + dy, 0x0);
      }
    }
  }

  while (1)
    ;

  return 0;
}
