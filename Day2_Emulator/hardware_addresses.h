// DTEK-V harware addresses
#define VGA_FRAMEBUFFER     0x08000000 //writing to this address means writing to the screen
#define VGA_PIXELBUFFER_DMA 0x04000100 //handels transfer between memory and vga output
#define BUTTON_BASE         0x040000d0 //address to button on DE10-Lite board
#define SWITCH_BASE         0x04000010 //Address of DE10-Lite switch state
#define TIMER_BASE          0x04000020 //Address of DE10-Lite hardware timer