#include <stdio.h>
#include <stdlib.h>
#include "input.h"    
#include "game.h" 
#include "graphics.h"

int main(void) {
  printf("\033[2J"); // Clear screen
  printf("SPACE INVADERS-STYLE GAME - Press any key to start...\n");
  getchar();

   // init_system();     // initialize VGA, inputs, etc.
    init_game();       // load sprites, set score=0, etc.
    draw_frame();

    while (1) {
      handle_input();    // step 1: check buttons or keyboard
      update_game();     // step 2: move player, aliens, bullets
      draw_frame();      // step 3: render to VGA memory
      //  wait_vsync();      // (optional) sync with VGA refresh

      // Check for game over conditions
      if(is_game_over() || player_won()){
        show_game_over_screen();
        printf("Press 'r' to restart or 'q' to quit: ");
        char c = getchar();
        if (c == 'r'){
          init_game();
          printf("\033[2J");
        }
        else {
          break;
        }
      }

      // Small delay to make game playable in terminal
      // Remove this when moving to hardware with timer interrupt
      for(volatile int i = 0; i < 100000; i++);
    }
  // show_game_over_screen();
  // cleanup();

  printf("Thanks for playing!");
  return 0;
}

