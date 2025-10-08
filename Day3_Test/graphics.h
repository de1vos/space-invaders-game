#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <stdio.h>

#include "game.h"

// Color definitions (8-bit format)
#define COLOR_BLACK    0x00
#define COLOR_WHITE    0xFF
#define COLOR_RED      0xE0
#define COLOR_GREEN    0x1C
#define COLOR_BLUE     0x03
#define COLOR_YELLOW   0xFC
#define COLOR_CYAN     0x1F
#define COLOR_MAGENTA  0xE3

#define VGA_WIDTH 320 // Horizontal screen size
#define VGA_HEIGHT 240 // Vertical screen size
#define PIXEL_SCALE 4

// Main rendering function
void draw_frame(void);

// Helper drawing functions
void draw_block(int x, int y, int w, int h, unsigned char color);
void draw_line_h(int y, int x1, int x2, unsigned char color);
void draw_line_v(int x, int y1, int y2, unsigned char color);


#endif