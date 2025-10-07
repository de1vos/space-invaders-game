#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>

typedef enum {
    ACTION_NONE,     // = 0
    ACTION_LEFT,     // = 1
    ACTION_RIGHT,    // = 2
    ACTION_SHOOT,    // = 3
    ACTION_QUIT      // = 4
} Action;

Action get_action();

#endif