#include "font.h"

void writeChar(int x, int y, char c, const uint16_t color) {
  uint32_t index = FONT_HEIGHT * c;
  const uint8_t *font_bitmap = _ProggyClean_start + index;

  for (int dy = 0; dy < FONT_HEIGHT; dy++) {
    for (int dx = 0; dx < FONT_WIDTH; dx++) {
      if ((font_bitmap[dy] << dx) & 0x40u) {
        drawPixel(x + dx, y + dy, color);
      }
    }
  }
}

void writeString(int x, int y, const char *s, const uint16_t color) {
  for (uint32_t i = 0; s[i] != 0; i++) {
    writeChar( x + FONT_WIDTH * i, y, s[i], color);
  }
}
