#include "font/font.h"

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

int main(void) {
  initalizeDisplay();

  writeString(10, 10, "Hello, world!", 0x0000);

  while (1)
    ;

  return 0;
}
