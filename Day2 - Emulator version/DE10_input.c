#include "DE10_input.h"

// TODO: Replace with actual DE-10 GPIO addresses
#define BUTTON_BASE 0xFF200050  // Example - verify with your hardware
#define SWITCH_BASE 0xFF200040  // Example - verify with your hardware

// Button bit assignments (example - adjust to your wiring)
#define BTN_LEFT  (1 << 0)
#define BTN_RIGHT (1 << 1)
#define BTN_SHOOT (1 << 2)
#define BTN_QUIT  (1 << 3)

void init_de10_input(void) {
    // GPIO usually doesn't need initialization for reading
    // but you might need to set direction registers
    // TODO: Configure GPIO direction if needed
}

unsigned int read_buttons(void) {
    volatile unsigned int *button_ptr = (unsigned int *)BUTTON_BASE;
    return *button_ptr;
}

unsigned int read_switches(void) {
    volatile unsigned int *switch_ptr = (unsigned int *)SWITCH_BASE;
    return *switch_ptr;
}

Action get_hardware_action(void) {
    static unsigned int prev_buttons = 0;
    unsigned int buttons = read_buttons();
    
    // Edge detection: only trigger on button press, not hold
    unsigned int pressed = buttons & ~prev_buttons;
    prev_buttons = buttons;
    
    // Check which button was pressed
    if(pressed & BTN_LEFT) {
        return ACTION_LEFT;
    }
    if(pressed & BTN_RIGHT) {
        return ACTION_RIGHT;
    }
    if(pressed & BTN_SHOOT) {
        return ACTION_SHOOT;
    }
    if(pressed & BTN_QUIT) {
        return ACTION_QUIT;
    }
    
    // Alternative: use switches for continuous movement
    unsigned int switches = read_switches();
    if(switches & 0x01) {
        return ACTION_LEFT;
    }
    if(switches & 0x02) {
        return ACTION_RIGHT;
    }
    
    return ACTION_NONE;
}