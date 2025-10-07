#ifndef TIMER_H
#define TIMER_H

// Timer configuration for DE-10 board
// Adjust these based on your specific hardware setup

// Initialize timer for game loop (e.g., 60 Hz)
void init_timer(void);

// Enable timer interrupt
void enable_timer_interrupt(void);

// Disable timer interrupt
void disable_timer_interrupt(void);

// Timer interrupt service routine (ISR)
// This will be called automatically by hardware
void timer_isr(void) __attribute__((interrupt));

// Get elapsed time in milliseconds (for performance measurement)
unsigned long get_time_ms(void);

// Delay for specified milliseconds
void delay_ms(unsigned int ms);

#endif