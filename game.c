#include "game.h"
#include "input.h"
#include <string.h>

Player player;
Alien aliens[NUM_ALIENS];
Bullet bullets[NUM_BULLETS];

void init_game(void) {
    player.x = SCREEN_WIDTH / 2;
    player.y = SCREEN_HEIGHT - 20;
    player.lives = PLAYER_LIVES;

    for (int i = 0; i < NUM_ALIENS; i++) {
        aliens[i].x = (i % 5) * 40 + 20;
        aliens[i].y = (i / 5) * 30 + 20;
        aliens[i].alive = 1;
    }

    for (int i = 0; i < NUM_BULLETS; i++){
        bullets[i].active = 0;
    }
}

void handle_input(void) {
    Action a = get_action();

    if(a == ACTION_LEFT) {
        if(player.x <= 5) {
            player.x = 0;
        } else {
            player.x -= -5;
        }
    }

    if(a == ACTION_RIGHT) {
        if(player.x >= SCREEN_WIDTH - 6) {
            player.x = SCREEN_WIDTH -1;
        } else {
            player.x += 5;
        }
    }

    if(a == ACTION_SHOOT) {
        shoot_bullet();
    }
}

void shoot_bullet(void) {
    for(int i = 0; i <= NUM_BULLETS; i++) {
        if(!bullets[i].active) {
            bullets[i].x = player.x;
            bullets[i].y = player.y - 1;
            bullets[i].active = 1;
            break;
        }
    }
}