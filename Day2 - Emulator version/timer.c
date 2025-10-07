#include "timer.h"
#include "game.h"

// TODO: Replace these with actual DE-10 addresses
#define TIMER_BASE 0xFF202000  // Example address - verify with your hardware
#define TIMER_STATUS (TIMER_BASE + 0)
#define TIMER_CONTROL (TIMER_BASE + 4)
#define TIMER_PERIODL (TIMER_BASE + 8)
#define TIMER_PERIODH (TIMER_BASE + 12)

static volatile unsigned long system_ticks = 0;

void init_timer(void) {
    // TODO: Configure timer for 60 Hz (16.67ms period)
    // Example pseudo-code:
    // 1. Calculate period value based on clock frequency
    // 2. Write to TIMER_PERIODL and TIMER_PERIODH registers
    // 3. Set control register to start timer
    
    system_ticks = 0;
}

void enable_timer_interrupt(void) {
    // TODO: Enable interrupt in timer control register
    // Set appropriate bit in TIMER_CONTROL
}

void disable_timer_interrupt(void) {
    // TODO: Disable interrupt in timer control register
}

void timer_isr(void) {
    // TODO: Clear interrupt flag
    // volatile int *status = (int *)TIMER_STATUS;
    // *status = 0;  // Clear interrupt
    
    system_ticks++;
    
    // Game update could go here, or set a flag for main loop
    // update_game();
}

unsigned long get_time_ms(void) {
    // Assuming 60 Hz timer: 1 tick = 16.67ms
    return (system_ticks * 1000) / 60;
}

void delay_ms(unsigned int ms) {
    unsigned long start = get_time_ms();
    while(get_time_ms() - start < ms) {
        // Busy wait
    }
}