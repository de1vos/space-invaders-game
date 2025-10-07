#ifndef DE10_INPUT_H
#define DE10_INPUT_H

#include "input.h"

// Initialize GPIO for buttons/switches
void init_de10_input(void);

// Read hardware buttons/switches and return Action
// This replaces the terminal get_action() for hardware
Action get_hardware_action(void);

// Read raw button state (for debugging)
unsigned int read_buttons(void);

// Read raw switch state (for debugging)
unsigned int read_switches(void);

#endif