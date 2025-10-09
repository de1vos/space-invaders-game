#include <stdio.h>
#include <stdlib.h>
#include "DE10_input.h"    
#include "game.h" 
#include "graphics.h"
#include "performance_monitor.h"

int main(void) {
    // Initialize hardware
    init_timer();

    // Initialise game state
    init_game();       // load sprites, set score=0, etc.

 

    // Game loop control
    int game_tick = 0;
    int update_rate = 2;

    // Main game loop
    draw_frame();

    uint32_t start_cycles_lo = read_cycles_lo();
    uint32_t start_cycles_hi = read_cycles_hi();
    uint32_t start_instructions_lo = read_instructions_lo();
    uint32_t start_instructions_hi = read_instructions_hi();
    uint32_t start_data_lo = numberof_memoryinstructions_lo();
    uint32_t start_data_hi = numberof_memoryinstructions_hi();
    uint32_t start_cachemissI_lo = numberof_I_cachemiss_lo();
    uint32_t start_cachemissI_hi = numberof_I_cachemiss_hi();
    uint32_t start_cachemissD_lo = numberof_D_cachemiss_lo();
    uint32_t start_cachemissD_hi = numberof_D_cachemiss_hi();
    uint32_t start_data_hazards_lo = data_hazards_lo();
    uint32_t start_data_hazards_hi = data_hazards_hi();
    uint32_t start_ALU_STALL_lo = ALU_stall_lo();
    uint32_t start_ALU_STALL_hi = ALU_stall_hi();
    uint32_t start_stall_I_lo = numberofstalls_I_lo();
    uint32_t start_stall_D_lo = numberofstalls_D_lo();

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
        break;
      }

      // Small delay to make game playable in terminal
      // Remove this when moving to hardware with timer interrupt
      for (volatile int i = 0; i < 50000; i++);
    }

    uint32_t end_cycles_lo = read_cycles_lo();
    uint32_t end_cycles_hi = read_cycles_hi();
    uint32_t end_instructions_lo = read_instructions_lo();
    uint32_t end_instructions_hi = read_instructions_hi();
    uint32_t end_data_lo = numberof_memoryinstructions_lo();
    uint32_t end_data_hi = numberof_memoryinstructions_hi();
    uint32_t end_cachemissI_lo = numberof_I_cachemiss_lo();
    uint32_t end_cachemissI_hi = numberof_I_cachemiss_hi();
    uint32_t end_cachemissD_lo = numberof_D_cachemiss_lo();
    uint32_t end_cachemissD_hi = numberof_D_cachemiss_hi();
    uint32_t end_data_hazards_lo = data_hazards_lo();
    uint32_t end_data_hazards_hi = data_hazards_hi();
    uint32_t end_ALU_STALL_lo = ALU_stall_lo();
    uint32_t end_ALU_STALL_hi = ALU_stall_hi();
    uint32_t end_stall_I_lo = numberofstalls_I_lo();
    uint32_t end_stall_D_lo = numberofstalls_D_lo();

print("cycles_lo: ");
print_dec(end_cycles_lo - start_cycles_lo);
print("\n cycles_hi: ");
print_dec(end_cycles_hi - start_cycles_hi);

print("\n instructions_lo: ");
print_dec(end_instructions_lo - start_instructions_lo);
print("\n instructions_hi: ");
print_dec(end_instructions_hi - start_instructions_hi);

print("\n numberof_memoryinstrictions_lo: ");
print_dec(end_data_lo - start_data_lo);
print("\n numberof_memoryinstructions_hi: ");
print_dec(end_data_hi - start_data_hi);

print("\n cachemissI_lo: ");
print_dec(end_cachemissI_lo - start_cachemissI_lo);
print("\n cachemissI_hi: ");
print_dec(end_cachemissI_hi - start_cachemissI_hi);

print("\n cachemissD_lo: ");
print_dec(end_cachemissD_lo - start_cachemissD_lo);
print("\n cachemissD_hi: ");
print_dec(end_cachemissD_hi - start_cachemissD_hi);

print("\n data_hazards_lo");
print_dec(end_data_hazards_lo - start_data_hazards_lo);
print("\n data_hazards_hi");
print_dec(end_data_hazards_hi - start_data_hazards_hi);

print("\n ALU_STALL_lo: ");
print_dec(end_ALU_STALL_lo - start_ALU_STALL_lo);
print("\n ALU_STALL_hi");
print_dec(end_ALU_STALL_hi - start_ALU_STALL_hi);

print("\n I_STALL_lo: ");
print_dec(end_stall_I_lo - start_stall_I_lo);
print("\n D_STALL_lo");
print_dec(end_stall_D_lo - start_stall_D_lo);

  // show_game_over_screen();
  // cleanup();
  return 0;
}

