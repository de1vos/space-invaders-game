// Modified VGA test - trying different pixel formats
#define VGA_FRAMEBUFFER 0x08000000 // 320 x 240 resolution

// 8-bit indexed colors
#define COLOR_BLACK   0x00
#define COLOR_WHITE   0xFF
#define COLOR_RED     0xE0 
#define COLOR_GREEN   0x1C  
#define COLOR_BLUE    0x03  
#define COLOR_YELLOW  0xFC

void handle_interrupt(void){
}

int main(void) {
    // Try 8-bit format first
    volatile unsigned char *framebuffer8 = (unsigned char *)VGA_FRAMEBUFFER;
    
    // Clear to black
    for(int i = 0; i < 320 * 240; i++) {
        framebuffer8[i] = COLOR_BLACK;
    }
    
    // Red square top-left (solid fill)
    for(int y = 10; y < 60; y++) {
        for(int x = 10; x < 60; x++) {
            framebuffer8[y * 320 + x] = COLOR_RED;
        }
    }
    
    // Green square top-right
    for(int y = 10; y < 60; y++) {
        for(int x = 260; x < 310; x++) {
            framebuffer8[y * 320 + x] = COLOR_GREEN;
        }
    }
    
    // Blue square bottom-left
    for(int y = 180; y < 230; y++) {
        for(int x = 10; x < 60; x++) {
            framebuffer8[y * 320 + x] = COLOR_BLUE;
        }
    }
    
    // White square center
    for(int y = 95; y < 145; y++) {
        for(int x = 135; x < 185; x++) {
            framebuffer8[y * 320 + x] = COLOR_WHITE;
        }
    }

    // Yellow square bottom-right
    for(int y = 180; y < 230; y++) {
        for(int x = 260; x < 310; x++){
            framebuffer8[y * 320 + x] = COLOR_YELLOW;
        }
    }
    
    while(1);
    
    return 0;
}