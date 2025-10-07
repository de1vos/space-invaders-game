#include "game.h"
#include "input.h"
#include "graphics.h"
#include <string.h>
#include <stdio.h>

Player player;
Alien aliens[NUM_ALIENS];
Bullet bullets[NUM_BULLETS];

static int alien_direction = 1;      // 1 = right, -1 = left
static int alien_move_counter = 0;
static int alien_speed = 10;         // Lower = faster

void init_game(void) {
    player.x = SCREEN_WIDTH / 2; // Player position initialisation
    player.y = SCREEN_HEIGHT - 2; // Player position initialisation
    player.lives = PLAYER_LIVES;
    player.score = 0;

    for (int i = 0; i < NUM_ALIENS; i++) { // Sets rows of 5 of aliens
        aliens[i].x = (i % 5) * 12 + 10; // Intra-row position
        aliens[i].y = (i / 5) * 4 + 2; // Inter-row position
        aliens[i].alive = 1;
    }

    for (int i = 0; i < NUM_BULLETS; i++){
        bullets[i].active = 0;
    }
}

int handle_input(void) {
    Action a = get_action();

    if (a == ACTION_QUIT) {
        return 1;
    }

    if (a == ACTION_LEFT) {
        if(player.x == 0) {
            player.x = 0;
        } else {
            player.x -= 1;
        }
    }

    if (a == ACTION_RIGHT) {
        if(player.x == SCREEN_WIDTH - 1) {
            player.x = SCREEN_WIDTH -1;
        } else {
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
                    player.score += POINTS_PER_ALIEN;
                }
            }
        }
    }
    // Alien movement
    alien_move_counter++;
    if (alien_move_counter >= alien_speed){ 
        alien_move_counter = 0;

        //Check if any alive alien hit edge
        int hit_edge = 0;
        for (int i = 0; i < NUM_ALIENS; i++){
            if (aliens[i].alive){
                if ((alien_direction == 1 && aliens[i].x >= SCREEN_WIDTH - 2) || 
                   (alien_direction == -1 && aliens[i].x <= 1)) {
                    hit_edge = 1;
                    break;
                }
            }
        }
        if (hit_edge) {
            // Change direction and move down
            alien_direction *= -1;
            for (int i = 0; i < NUM_ALIENS; i++){
                aliens[i].y += 1;

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
    if (player.lives <= 0) {
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
    printf("\033[2J\033[H"); // Clear screen
    printf("\n\n\n");
    printf("  =====================================\n");

    if (player_won()){
        printf("                 YOU WIN!\n");
    }
    else {
        printf("                 YOU LOSE!\n");
    }

    printf("  =====================================\n");
    printf("\n");
    printf("             Final Score: %d\n", player.score);
    printf("             Lives Left: %d\n", player.lives);
    printf("\n");
    printf("  =====================================\n");
    printf("\n");
}