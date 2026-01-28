#include "image.h"

#define REG_DISPCNT (*(volatile unsigned short *)0x04000000)
#define VRAM ((volatile unsigned short *)0x06000000)

#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 160

#define BG_MODE3 (3)
#define BG2_ON (1 << 10)

void MemCpy16bit(unsigned short *source, unsigned short *target,
                 unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    *(target++) = *(source++);
  }
}

int main(void) {
  // BGモード3, BG2を有効にする
  REG_DISPCNT = BG2_ON | BG_MODE3;

  MemCpy16bit(imageData, VRAM, DISPLAY_WIDTH * DISPLAY_HEIGHT);

  while (1)
    ;

  return 0;
}
