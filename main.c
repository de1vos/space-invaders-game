#include <stdio.h>
#include <stdlib.h>
#include "DE10_input.h"    
#include "game.h" 
#include "graphics.h"
#include "hardware_addresses.h"

int main(void) {
    // Initialize hardware
    init_timer();

    // Initiate DMA
    // init_dma();

    // Initialise game state
    init_game(); // load sprites, set score=0, etc.

    // Game loop control
    int game_tick = 0;
    int update_rate = 1;

    // Draw initial game state
    draw_frame();
    // swap_buffers();

    while (1) {
      // Get input from hardware switches and buttons
      handle_input(); // Do player action relative to inputs: Move or shoot

      game_tick++;
      if(game_tick >= update_rate){
        update_game();     // Move aliens, bullets, update bullet-alien & player-alien collision conditions
        game_tick = 0;
      }

      draw_frame();      // Render updated game state to VGA display
      // swap_buffers();

      // Game over
      if(is_game_over() || player_won()){
          break; // If game over, end game
      }

      // Small delay to make game playable in terminal
      // Remove this when moving to hardware with timer interrupt
      // SIDE EFFECT: Enables us to have synchronization with the display framerate
      // -> 50000 seems to be a sweet spot on the display we tested
      for (volatile int i = 0; i < 50000; i++);
    }
  return 0;
}

