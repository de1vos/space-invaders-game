// Quick VGA test program - compile and run this FIRST
// to verify your framebuffer address is correct
// Compile: gcc test_vga.c -o test_vga (or with your DE10 toolchain)

#define VGA_FRAMEBUFFER 0x08000000

// Color definitions (RGB565)
#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_YELLOW  0xFFE0

int main(void) {
    volatile unsigned short *framebuffer = (unsigned short *)VGA_FRAMEBUFFER;
    
    // Test 1: Fill entire screen with red
    for(int i = 0; i < 320 * 240; i++) {
        framebuffer[i] = COLOR_RED;
    }
    
    // Wait
    for(volatile int i = 0; i < 5000000; i++);
    
    // Test 2: Fill with green
    for(int i = 0; i < 320 * 240; i++) {
        framebuffer[i] = COLOR_GREEN;
    }
    
    // Wait
    for(volatile int i = 0; i < 5000000; i++);
    
    // Test 3: Fill with blue
    for(int i = 0; i < 320 * 240; i++) {
        framebuffer[i] = COLOR_BLUE;
    }
    
    // Wait
    for(volatile int i = 0; i < 5000000; i++);
    
    // Test 4: Draw some colored blocks
    // Clear to black
    for(int i = 0; i < 320 * 240; i++) {
        framebuffer[i] = COLOR_BLACK;
    }
    
    // Red square top-left
    for(int y = 10; y < 60; y++) {
        for(int x = 10; x < 60; x++) {
            framebuffer[y * 320 + x] = COLOR_RED;
        }
    }
    
    // Green square top-right
    for(int y = 10; y < 60; y++) {
        for(int x = 260; x < 310; x++) {
            framebuffer[y * 320 + x] = COLOR_GREEN;
        }
    }
    
    // Blue square bottom-left
    for(int y = 180; y < 230; y++) {
        for(int x = 10; x < 60; x++) {
            framebuffer[y * 320 + x] = COLOR_BLUE;
        }
    }
    
    // Yellow square bottom-right
    for(int y = 180; y < 230; y++) {
        for(int x = 260; x < 310; x++) {
            framebuffer[y * 320 + x] = COLOR_YELLOW;
        }
    }
    
    // White square center
    for(int y = 95; y < 145; y++) {
        for(int x = 135; x < 185; x++) {
            framebuffer[y * 320 + x] = COLOR_WHITE;
        }
    }
    
    // If you see colored squares in the corners and center, VGA is working!
    
    while(1);  // Loop forever
    
    return 0;
}