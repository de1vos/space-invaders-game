#ifndef INPUT_H
#define INPUT_H
#include <stdio.h>

typedef enum {
    ACTION_NONE,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_SHOOT,
    ACTION_QUIT
} Action;

Action get_action();

#endif