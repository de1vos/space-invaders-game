#include <stdio.h>
#include <stdlib.h>
#include "DE10_input.h"    
#include "game.h" 
#include "graphics.h"

int main(void) {
    // Initialize hardware
    init_timer();

    // Initialise game state
    init_game();       // load sprites, set score=0, etc.

    // Game loop control
    int game_tick = 0;
    int update_rate = 15;

    // Main game loop
    draw_frame();

    while (1) {
      // Get input from hardware switches and buttons

      handle_input();
      game_tick++;
      if(game_tick >= update_rate){
        update_game();     // step 2: move player, aliens, bullets
        game_tick = 0;
      }

      draw_frame();      // step 3: render to VGA memory
      //  wait_vsync();      // (optional) sync with VGA refresh

      // Check for game over conditions
      if(is_game_over() || player_won()){
        show_game_over_screen();
      }

      // Small delay to make game playable in terminal
      // Remove this when moving to hardware with timer interrupt
      for (volatile int i = 0; i < 50000; i++);
    }
  // show_game_over_screen();
  // cleanup();
  return 0;
}

