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

// Move bullets and check for off-screen
void update_game(void) {
    for(int i = 0; i < NUM_BULLETS; i++) {
        if(bullets[i].active) {
            bullets[i].y -= 1;  // move bullet up

            // If bullet goes off-screen, deactivate it
            if(bullets[i].y < 0) {
                bullets[i].active = 0;
            }

            // Check collision with aliens
            for(int j = 0; j < NUM_ALIENS; j++) {
                if(aliens[j].alive &&
                   bullets[i].x == aliens[j].x &&
                   bullets[i].y == aliens[j].y) {
                    aliens[j].alive = 0;   // kill alien
                    bullets[i].active = 0; // remove bullet
                }
            }
        }
    }

    // TODO: later move aliens here
}
