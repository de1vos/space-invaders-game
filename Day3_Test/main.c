#include <stdio.h>
#include <stdlib.h>
#include "DE10_input.h"    
#include "game.h" 
#include "graphics.h"

int main(void) {
    // Initialize hardware
    init_timer();

    // Initiate DMA
    init_dma();

    // Initialise game state
    init_game();       // load sprites, set score=0, etc.

    // Game loop control
    int game_tick = 0;
    int update_rate = 2;

    // Main game loop
    draw_frame();
    swap_buffers();

    while (1) {
      // Get input from hardware switches and buttons

      handle_input();
      game_tick++;
      if(game_tick >= update_rate){
        update_game();     // step 2: move player, aliens, bullets
        game_tick = 0;
      }

      // Check for game over conditions
      if(is_game_over() || player_won()){
        show_game_over_screen();
        break;
      }

      draw_frame();      // step 3: render to VGA memory
      swap_buffers();

      // Small delay to make game playable in terminal
      // Remove this when moving to hardware with timer interrupt
      // for (volatile int i = 0; i < 50000; i++);
    }
  // show_game_over_screen();
  return 0;
}

