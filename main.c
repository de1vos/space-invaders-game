#include <stdio.h>
#include <stdlib.h>
#include "input.h"    
#include "game.h" 
#include "graphics.h"

int main(void) {
   // init_system();     // initialize VGA, inputs, etc.
    init_game();       // load sprites, set score=0, etc.

    while (1) {
        handle_input();    // step 1: check buttons or keyboard
        update_game();     // step 2: move player, aliens, bullets
        draw_frame();      // step 3: render to VGA memory
      //  wait_vsync();      // (optional) sync with VGA refresh
    }

   // show_game_over_screen();
   // cleanup();
    return 0;
}

