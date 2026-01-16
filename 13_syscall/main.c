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
#define BIOS_IRQ_EOI (*(volatile unsigned short *)0x3007FF8)
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
    BIOS_IRQ_EOI |= IRQ_VBLANK;
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

int DivSyscall(int a, int b) { __asm__("swi 0x06 * 0x10000"); }

int main(void) {
  initalizeDisplay();
  initIrq();

  // VBlankまで待つ
  vblankFlg = 0;
  while (!vblankFlg) {
  }

  drawPixel(
      DivSyscall(DISPLAY_WIDTH, 2), DivSyscall(DISPLAY_HEIGHT, 2), 0x0000);

  while (1)
    ;

  return 0;
}
