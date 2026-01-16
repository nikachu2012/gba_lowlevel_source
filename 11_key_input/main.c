#define REG_DISPCNT (*(volatile unsigned short *)0x04000000)
#define VRAM ((volatile unsigned short *)0x06000000)

#define REG_KEYINPUT (*(volatile unsigned short *)0x4000130)

#define BTN_RIGHT (1 << 4)
#define BTN_LEFT (1 << 5)
#define BTN_UP (1 << 6)
#define BTN_DOWN (1 << 7)

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

int main(void) {
  initalizeDisplay();

  int x = 0, y = 0;
  while (1) {
    // Pressed=0, Released=1
    if (!(REG_KEYINPUT & BTN_UP))
      y--;
    if (!(REG_KEYINPUT & BTN_DOWN))
      y++;
    if (!(REG_KEYINPUT & BTN_LEFT))
      x--;
    if (!(REG_KEYINPUT & BTN_RIGHT))
      x++;

    // 次の点を描画
    drawPixel(x, y, 0x0000);

    // ウェイト
    for (int i = 0; i < 1024; i++) {
    }
  }

  return 0;
}
