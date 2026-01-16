#define REG_DISPCNT (*(volatile unsigned short *)0x04000000)
#define VRAM ((volatile unsigned short *)0x06000000)

unsigned short d;
unsigned short RED_COLOR = 0x001f;

int main(void)
{
    REG_DISPCNT = 0x0403;

    // 全ピクセル赤にする
    for (int i = 0; i < 240 * 160; i++)
    {
        VRAM[i] = RED_COLOR;
    }

    while (1)
        ;

    return 0;
}
