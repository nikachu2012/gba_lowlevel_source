#define REG_DISPCNT (*(volatile unsigned short *)0x04000000)
#define VRAM ((volatile unsigned short *)0x06000000)
#define REG_DISPSTAT (*(volatile unsigned short *)0x4000004)

#define REG_KEYINPUT (*(volatile unsigned short *)0x4000130)

#define BTN_RIGHT (1 << 4)
#define BTN_LEFT (1 << 5)
#define BTN_UP (1 << 6)
#define BTN_DOWN (1 << 7)

// 割り込み関連
#define IRQ_HANDLER (*(volatile unsigned int *)0x03007FFC)
#define REG_IME (*(volatile unsigned short *)0x4000208)
#define REG_IE (*(volatile unsigned short *)0x4000200)
#define REG_IF (*(volatile unsigned short *)0x4000202)

#define IRQ_VBLANK (1 << 0)

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

volatile int vblankFlg = 0;

void irqHandler() {
  REG_IME = 0;

  unsigned short flg = REG_IF;

  if (flg & IRQ_VBLANK) {
    // irq vblank
    vblankFlg = 1;
    REG_IF = IRQ_VBLANK;
  }

  REG_IME = 1;
}

void initIrq() {
  REG_IME = 0;

  IRQ_HANDLER = (unsigned int)irqHandler;

  REG_IE |= IRQ_VBLANK;

  // VBlankでのIRQを有効にする
  REG_DISPSTAT |= 1 << 3;

  REG_IME = 1;
}

int main(void) {
  initalizeDisplay();
  initIrq();

  int x = 0, y = 0;

  while (1) {
    // VBlankまで待つ
    vblankFlg = 0;
    while (!vblankFlg) {
    }

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
  }

  return 0;
}
