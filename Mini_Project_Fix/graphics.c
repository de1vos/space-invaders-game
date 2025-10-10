#include "graphics.h"
#include "game.h"
#include "hardware_addresses.h"
#include <string.h> // Probably redundant here, leftover from previous version

volatile unsigned char *current_back_buffer = (unsigned char *)BACK_BUFFER;

void init_dma(void) { // Not used
    volatile unsigned int *dma_ctrl = (volatile unsigned int *)VGA_PIXELBUFFER_DMA;
    
    // Offset 0x4: Set back buffer address (offset +1 in int pointer = +4 bytes)
    *(dma_ctrl + 1) = BACK_BUFFER;
    
    // Offset 0x8: Set resolution (offset +2)
     // *(dma_ctrl + 2) = 0x00F00140;  // 240 rows x 320 cols
    
    current_back_buffer = (unsigned char *)BACK_BUFFER;
}

void swap_buffers(void) { // Not used
    volatile unsigned int *dma_ctrl = (volatile unsigned int *)VGA_PIXELBUFFER_DMA; // current_back_buffer;
    
    // Offset 0x0: Write to buffer register to request swap
    *dma_ctrl = 1; // current_back_buffer;
    
    // Offset 0xC: Wait for S bit (status bit 0) to show that swap is ready
    while (*(dma_ctrl + 3) & 0x1) {
        // Busy wait - swap in progress
    }
    
     // After swap, read which buffer (offst 0x0) is now the front buffer
    unsigned int current_front = *dma_ctrl;
    
    // Draw to whichever buffer is NOT being displayed
    if (current_front == VGA_FRAMEBUFFER) {
        current_back_buffer = (unsigned char *)BACK_BUFFER;
    } else {
        current_back_buffer = (unsigned char *)VGA_FRAMEBUFFER;
    }
}

void draw_block(volatile unsigned char *fb, int x, int y, int w, int h, unsigned char color){
    for (int dy = 0; dy < h; dy++) { // Offset on y-axis
        for (int dx = 0; dx < w; dx++) { // Offset on x-axis
            int px = x + dx;
             int py = y + dy;
            if (px >= 0 && px < VGA_WIDTH && py >= 0 && py < VGA_HEIGHT) { // If not exceeding frame
                fb[py * VGA_WIDTH + px] = color;
            }
        }
    }
}

void draw_line_h(volatile unsigned char *fb, int y, int x1, int x2, unsigned char color){
    if (y < 0 || y >= VGA_HEIGHT) return; // If outside y-frame, stop

    for (int x = x1; x <= x2 && x < VGA_WIDTH; x++){ // Between x-points, write a horizontal line
        if (x >= 0) {
            fb[y * VGA_WIDTH + x] = color;
        }
    }
}

void draw_line_v(volatile unsigned char *fb, int x, int y1, int y2, unsigned char color){
    if (x < 0 || x >= VGA_WIDTH) return; // If outside x-frame, stop

    for (int y = y1; y <= y2 && y < VGA_HEIGHT; y++) { // Between y-points, write a vertical line
        if (y >= 0) {
            fb[y * VGA_WIDTH + x] = color;
        }
    }
}

// Instead of 2D char array, draw directly to framebuffer
void draw_frame(void){
    volatile unsigned char *framebuffer = (unsigned char *)VGA_FRAMEBUFFER; // current_back_buffer;

    // Reinitialise screen to black
    for (int i = 0; i < 320 * 240; i++){
        framebuffer[i] = COLOR_BLACK;
    }

    // Draw border
    draw_line_h(framebuffer, 0, 0, VGA_WIDTH-1, COLOR_WHITE); // Top border
    draw_line_h(framebuffer, VGA_HEIGHT-1, 0 , VGA_WIDTH-1, COLOR_WHITE); // Bottom border
    draw_line_v(framebuffer, 0, 0, VGA_HEIGHT-1, COLOR_WHITE); // Left border
    draw_line_v(framebuffer, VGA_WIDTH-1, 0, VGA_HEIGHT-1, COLOR_WHITE); // Right border

    
     // Draw player
    int player_px = player.x * PIXEL_SCALE; // Logical x * pixel multiplier = Actual x
    int player_py = player.y * PIXEL_SCALE; // Logical y * pixel multiplier = Actual y
    draw_block(framebuffer, player_px, player_py, 5, 5, COLOR_WHITE); // Player is a 5x5 pixel white square

    // Draw bullets    
    for(int i = 0; i < NUM_BULLETS; i++) {
        if(bullets[i].active) {
            int bullet_px = bullets[i].x * PIXEL_SCALE; // Logical x * pixel multiplier = Actual x
            int bullet_py = bullets[i].y * PIXEL_SCALE; // Logical y * pixel multiplier = Actual y
            draw_block(framebuffer, bullet_px, bullet_py, 2, 3, COLOR_YELLOW); // Bullet is a 2x3 pixel yellow rectangle
        }
    }
    // Draw aliens
    for(int i = 0; i < NUM_ALIENS; i++) {
        if(aliens[i].alive) {
            int alien_px = aliens[i].x * PIXEL_SCALE; // Logical x * pixel multiplier = Actual x
            int alien_py = aliens[i].y * PIXEL_SCALE; // Logical y * pixel multiplier = Actual y
            draw_block(framebuffer, alien_px, alien_py, 4, 4, COLOR_RED); // Alien is a 4x4 pixel red square
        }
    }

   // Score indicator
    int score_bars = player.score / 10; // Number of score bars = Number of aliens killed
    if (score_bars > 20) score_bars = 20; // Max number of score bars
    for (int i = 0; i < score_bars; i++) { // For every alien killed, write a 1x5 pixel green rectangle
        draw_block(framebuffer, VGA_WIDTH - 10 - (i*2), 5, 1, 10, COLOR_GREEN);
    }
}