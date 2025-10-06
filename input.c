#include "input.h"
#include <stdio.h>

Action get_action() { // Defines get_action = our input function
    char c = getchar(); // read one character from terminal
    switch(c) {
        case 'a': return ACTION_LEFT;
        case 'd': return ACTION_RIGHT;
        case 'm': return ACTION_SHOOT;
        case 'q': return ACTION_QUIT;
        default: return ACTION_NONE;
    }
}
