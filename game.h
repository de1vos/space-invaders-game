#ifndef GAME_H
#define GAME_H
#include <stdio.h>

#define NUM_ALIENS 10
#define NUM_BULLETS 100
#define PLAYER_LIVES 3
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define POINTS_PER_ALIEN 10

typedef struct {
    int x, y;
    int alive;
} Alien;

typedef struct {
    int x, y;
    int active;
} Bullet;

typedef struct {
    int x, y;
    int lives;
    int score;
} Player;

//initializes structures as extern so we can call them from our other functions/files
extern Player player;                  
extern Alien aliens[NUM_ALIENS];
extern Bullet bullets[NUM_BULLETS];

// Initialize game state
void init_game(void);

// Update all game logic: move aliens, bullets, check collisions
void update_game(void);

// Draw the current game state to the VGA framebuffer
void draw_frame(void);

// Handle player input (buttons or keyboard)
void handle_input(void);

// Shoot a bullet from the player
void shoot_bullet(void);

// Check if all aliens are defeated
int all_aliens_dead(void);

// Display the game over screen
void show_game_over_screen(void);

#endif 
