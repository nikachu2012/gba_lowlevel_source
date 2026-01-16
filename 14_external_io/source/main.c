#include <gba_console.h>
#include <gba_input.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_video.h>
#include <stdio.h>
#include <stdlib.h>

#define REG_RCNT (*(volatile uint16_t *)(0x04000134))
#define REG_SIOCNT (*(volatile uint16_t *)(0x04000128))
#define REG_SIODATA32 (*(volatile uint32_t *)(0x04000120))

void initConnection() {
  // reset RCNT
  REG_RCNT = 0;

  // set use external clock
  REG_SIOCNT &= ~1;

  // use 32 bit mode
  REG_SIOCNT |= (1 << 12);
}

uint32_t exchange32(uint32_t data) {
  // set data
  REG_SIODATA32 = data;

  // start bit set 0
  REG_SIOCNT &= ~(1 << 7);

  // SO set 0
  REG_SIOCNT &= ~(1 << 3);

  // start bit to 1
  REG_SIOCNT |= (1 << 7);

  // SO set 1 or 0
  if (data & 1) {
    REG_SIOCNT |= (1 << 3);
  } else {
    REG_SIOCNT &= ~(1 << 3);
  }

  // wait start bit 0
  while ((REG_SIOCNT & (1 << 7)))
    ;

  return REG_SIODATA32;
}

int main(void) {
  consoleDemoInit();
  initConnection();

  iprintf("Data exchange test\n");

  uint32_t data = exchange32(0x10101010);
  iprintf("%lx\n", data);

  while (1)
    ;
}
