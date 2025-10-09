#include "game.h"
#include "DE10_input.h"
#include "graphics.h"
#include <string.h> // unnecessary probably, leftover from terminal-build
#include <stdio.h> // Unnecessary probably, we don't use printf, leftover from terminal-build

Player player;
Alien aliens[NUM_ALIENS];
Bullet bullets[NUM_BULLETS];

static int alien_direction = 1;      // 1 = right, -1 = left
static int alien_move_counter = 0;
static int alien_speed = 5;         // Lower = faster

void init_game(void) {
    player.x = (VGA_WIDTH / PIXEL_SCALE) / 2; // Player position initialisation, logical units
    player.y = (VGA_HEIGHT / PIXEL_SCALE) - 2; // Player position initialisation, logical units
    player.lives = PLAYER_LIVES;
    player.score = 0;

    for (int i = 0; i < NUM_ALIENS; i++) { // Sets rows of 5 of aliens
        aliens[i].x = (i % 5) * 12 + 10; // Intra-row position, pixel units
        aliens[i].y = (i / 5) * 4 + 2; // Inter-row position, pixel units
        aliens[i].alive = 1;
    }

    for (int i = 0; i < NUM_BULLETS; i++){
        bullets[i].active = 0;
    }
}

int handle_input(void) {
    Action a = get_hardware_action();

    if (a == ACTION_QUIT) {
        return 1;
    }

    if (a == ACTION_LEFT) {
        if(player.x > 0 ) {
            player.x -= 1;
        }
    }

    if (a == ACTION_RIGHT) {
        if(player.x < (VGA_WIDTH / PIXEL_SCALE) - 1) { // Logical unit check, so that block doesn't go out-of-bounds
            player.x += 1;
        }
    }

    if (a == ACTION_SHOOT) {
        shoot_bullet();
    }
    return 0;
}

void shoot_bullet(void) {
    for(int i = 0; i < NUM_BULLETS; i++) {
        if(!bullets[i].active) {
            bullets[i].x = player.x;
            bullets[i].y = player.y - 1;
            bullets[i].active = 1;
            break;
        }
    }
}

// State changer: Move aliens, bullets, check for off-screen position
void update_game(void) {
    // Bullet movement
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
                    bullets[i].y == aliens[j].y) { // If superposition of bullet and alien
                    aliens[j].alive = 0;   // kill alien
                    bullets[i].active = 0; 
                    player.score += POINTS_PER_ALIEN;
                }
            }
        }
    }
    // Alien movement
    alien_move_counter++;
    if (alien_move_counter >= alien_speed){ 
        alien_move_counter = 0;

        int max_logical_x = (VGA_WIDTH / PIXEL_SCALE) - 2;  // 320/4 - 2 = 78

        //Check if any alive alien hit edge
        int hit_edge = 0;
        for (int i = 0; i < NUM_ALIENS; i++){
            if (aliens[i].alive){
                if ((alien_direction == 1 && aliens[i].x >= max_logical_x) || 
                   (alien_direction == -1 && aliens[i].x <= 1)) {
                    hit_edge = 1;
                    break;
                }
            }
        }
        // If any alien has hit an edge, do the following
        if (hit_edge) {
            //  Change direction and move down
            alien_direction *= -1;
            for (int i = 0; i < NUM_ALIENS; i++){
                aliens[i].y += 6;

                // Check if alien reached player
                if (aliens[i].y >= player.y){
                    player.lives = 0;
                }
            }
        }
        else {
            // Move horizontally
            for (int i = 0; i < NUM_ALIENS; i++) {
                aliens[i].x += alien_direction;
            }
        }
    }
}

int all_aliens_dead(void){
    for (int i = 0; i < NUM_ALIENS; i++){
        if (aliens[i].alive) {
            return 0;
        }
    }
    return 1;
}

int is_game_over(void){
    if ( player.lives <= 0) {
        return 1;
    }
    for (int i = 0; i < NUM_ALIENS; i++) {
        if (aliens[i].alive && aliens[i].y >= player.y){
            return 1;
        }
    }
    return 0;
}

int player_won(void){
    return all_aliens_dead();
}

void show_game_over_screen(void){
}