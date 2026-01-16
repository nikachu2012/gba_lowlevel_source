#pragma once

#include <stdint.h>

#define FONT_WIDTH 7
#define FONT_HEIGHT 13

// main関数内のdrawPixelを使用できるように定義
extern void drawPixel(int x, int y, unsigned short s);

extern const uint8_t _ProggyClean_start[];
extern const uint8_t _ProggyClean_end[];
extern const uint32_t _binary_ProggyClean_bin_size;

/**
 * @brief 1文字を指定座標に出力
 *
 * @param writer 出力用クラス
 * @param x x座標(左上を0,0とする)
 * @param y y座標
 * @param c 出力する文字
 * @param color 16ビットカラー
 */
void writeChar(int x, int y, char c, const uint16_t color);

/**
 * @brief 文字列を指定座標に出力
 *
 * @param writer
 * @param x
 * @param y
 * @param s
 * @param color
 */
void writeString(int x, int y, const char *s, const uint16_t color);
