#define REG_DISPCNT (*(volatile unsigned short *)0x04000000)
#define VRAM ((volatile unsigned short *)0x06000000)

int main(void)
{
    REG_DISPCNT = 0x0403;

    // 全ピクセル赤にする
    for (int i = 0; i < 240 * 160; i++)
    {
        // 赤色にする
        VRAM[i] = 0x001f;
    }

    while (1)
        ;

    return 0;
}
