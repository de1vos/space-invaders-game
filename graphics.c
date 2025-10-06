#include "graphics.h"
#include <stdio.h>
#include <string.h>

void draw_frame(void){
    // Use a simple 2D char array for terminal testing
    char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    memset(screen, '.', sizeof(screen));
    
    // Draw player
    screen[player.y][player.x] = 'W';

    // Draw bullets    
    for(int i = 0; i < NUM_BULLETS; i++) {
        if(bullets[i].active &&
           bullets[i].y >= 0 && bullets[i].y < SCREEN_HEIGHT &&
           bullets[i].x >= 0 && bullets[i].x < SCREEN_WIDTH) {
            screen[bullets[i].y][bullets[i].x] = '^';
        }
    }
    // Draw aliens
    for(int i = 0; i < NUM_ALIENS; i++) {
        if(aliens[i].alive &&
           aliens[i].y >= 0 && aliens[i].y < SCREEN_HEIGHT &&
           aliens[i].x >= 0 && aliens[i].x < SCREEN_WIDTH) {
            screen[aliens[i].y][aliens[i].x] = 'X';
        }
    }

    // Print screen to terminal
    printf("\033[H"); // move cursor to top-left
    for(int y = 0; y < SCREEN_HEIGHT; y++) {
        for(int x = 0; x < SCREEN_WIDTH; x++) {
            putchar(screen[y][x]);
        }
        putchar('\n');
    }

}