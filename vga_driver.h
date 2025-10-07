#ifndef VGA_DRIVER_H
#define VGA_DRIVER_H

// VGA display dimensions (typical for DE-10)
#define VGA_WIDTH 320
#define VGA_HEIGHT 240
#define VGA_CHAR_WIDTH 80   // Character mode: 80 columns
#define VGA_CHAR_HEIGHT 60  // Character mode: 60 rows

// Initialize VGA controller
void init_vga(void);

// Clear entire screen to black
void vga_clear_screen(void);

// Draw a pixel at (x, y) with color
void vga_draw_pixel(int x, int y, unsigned short color);

// Draw a character at character position (col, row)
void vga_draw_char(int col, int row, char c, unsigned short color);

// Draw a string at character position
void vga_draw_string(int col, int row, const char *str, unsigned short color);

// Common colors (RGB565 format)
#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_YELLOW  0xFFE0
#define COLOR_CYAN    0x07FF
#define COLOR_MAGENTA 0xF81F

#endif