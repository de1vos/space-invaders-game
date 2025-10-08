#include "DE10_input.h"
#include "hardware_addresses.h"
#include "game.h"

#define TIMER_BASE 0x04000020  // Example address - verify with your hardware
#define TIMER_STATUS (*(volatile unsigned int *)(TIMER_BASE))
#define TIMER_CONTROL (*(volatile unsigned int *)(TIMER_BASE + 0x04)) // write here to eg start or stop the timer
#define TIMER_PERIODL (*(volatile unsigned int *)(TIMER_BASE + 0x08))
#define TIMER_PERIODH (*(volatile unsigned int *)(TIMER_BASE + 0x0C))
#define SWITCH_ADDRESS 0x04000010
#define INTERRUPT_MASK (*(volatile unsigned int *)(SWITCH_ADDRESS + 8))
#define EDGE (*(volatile unsigned int *)(SWITCH_ADDRESS + 12))

void init_timer(void) {
    TIMER_CONTROL = 0x7;
    TIMER_PERIODL = 0xC6C0; 
    TIMER_PERIODH = 0x002D;   
    INTERRUPT_MASK = 0b1000000001;
    EDGE = 0b1000000001;
}

void timer_isr(void) {
    // TODO: Clear interrupt flag
    // volatile int *status = (int *)TIMER_STATUS;
    // *status = 0;  // Clear interrupt
    

    
    // Game update could go here, or set a flag for main loop
    // update_game();
}


int get_btn(void)
{
  volatile int *btn_pointer = (volatile int *)0x040000d0;

  return *btn_pointer & 0x1;
}

int get_sw(void)
{
  volatile int *sw_pointer = (volatile int *)0x04000010;

  return *sw_pointer & 0x3FF;
}


Action get_hardware_action(void) {
    
    unsigned int switch_state = get_sw();
    unsigned int button_state = get_btn();
    
    // Check which button was pressed
    if((switch_state & 0b1000000000) == 0b1000000000) { 
        return ACTION_LEFT;
    }
    if((switch_state & 0b1) == 0b1) {
        return ACTION_RIGHT;
    }
    if(button_state) {
        return ACTION_SHOOT;
    }
    if((switch_state & 0b100000) == 0b100000) {
        return ACTION_QUIT;
    }
    return ACTION_NONE;
}

void handle_interrupt(unsigned cause) {
    TIMER_STATUS = 1;

    if(cause == 17 || cause == 18) {
        get_hardware_action();
    }
   
    
}
