#include "vga_driver.h"
#include <string.h>

// TODO: Replace with actual DE-10 VGA addresses
#define VGA_PIXEL_BASE 0xC8000000  // Example - pixel buffer base
#define VGA_CHAR_BASE  0xC9000000  // Example - character buffer base

void init_vga(void) {
    // VGA controller usually auto-initializes
    // But you might need to configure resolution or mode
    vga_clear_screen();
}

void vga_clear_screen(void) {
    // Character mode clear
    volatile char *char_buffer = (char *)VGA_CHAR_BASE;
    for(int i = 0; i < VGA_CHAR_WIDTH * VGA_CHAR_HEIGHT; i++) {
        char_buffer[i] = ' ';
    }
    
    // Pixel mode clear (if using pixel buffer)
    // volatile unsigned short *pixel_buffer = (unsigned short *)VGA_PIXEL_BASE;
    // for(int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
    //     pixel_buffer[i] = COLOR_BLACK;
    // }
}

void vga_draw_pixel(int x, int y, unsigned short color) {
    if(x < 0 || x >= VGA_WIDTH || y < 0 || y >= VGA_HEIGHT) {
        return;  // Out of bounds
    }
    
    volatile unsigned short *pixel_buffer = (unsigned short *)VGA_PIXEL_BASE;
    pixel_buffer[y * VGA_WIDTH + x] = color;
}

void vga_draw_char(int col, int row, char c, unsigned short color) {
    if(col < 0 || col >= VGA_CHAR_WIDTH || row < 0 || row >= VGA_CHAR_HEIGHT) {
        return;  // Out of bounds
    }
    
    // Character buffer format varies by hardware
    // Often it's: [char byte][color byte] or similar
    // TODO: Adjust based on your VGA controller format
    
    volatile char *char_buffer = (char *)VGA_CHAR_BASE;
    int offset = (row * VGA_CHAR_WIDTH + col) * 2;  // 2 bytes per char
    char_buffer[offset] = c;
    char_buffer[offset + 1] = (char)(color & 0xFF);  // Simplified color
}

void vga_draw_string(int col, int row, const char *str, unsigned short color) {
    int i = 0;
    while(str[i] != '\0' && col + i < VGA_CHAR_WIDTH) {
        vga_draw_char(col + i, row, str[i], color);
        i++;
    }
}