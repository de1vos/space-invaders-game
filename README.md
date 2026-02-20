# Space Invaders Game

Welcome to our **Space Invaders** game implementation in C.

This project was our contribution to a KTH computer engineering university course. The instructed goals of the project were to implement any project of our choosing with the requirement of incorporating some form of external hardware I/O into the project. Since we wanted to do a videogame, we chose to do this by outputting to screen using VGA transmission.

We structured our programming using a **modular approach** with a host of .c and .h files compartimentalising different logics:
- **Main program** execution in main.c, main.h
- **Game logic** in game.c, game.h
- **Input logic** in DE10_input.c, DE10_input.h
- **Graphics logic** in graphics.c, graphics.h
- Keeping track of **hardware memory addresses** in hardware_addresses.h
- Additionally: We used the **dtek-v library** for its pre-made functions in dtekv-lib.c, dtekv-lib.h

Here's some instructions on how to run the program:

**Mini Project: Space Invaders-style game**
Runs on a **DTEK-V board.**

**To run**: Needs Linux OS.
1. In terminal, go to the directory containing 'main.bin' file and all game-related files.
2. Reset the DTEK-V
3. Start JTAG connection if not yet active
4. Run main.bin via the terminal command "dtekv-run main.bin"

**Inputs**:
- Move left: Left-most switch in "up-position" on the DTEK-V board
- Move right: Right-most switch in "up-position" on the DTEK-V board
- Shoot: Press lower button on DTEK-V board
Outputs on a VGA-connected external display

**How to play**:
- The player move his spaceship horizontally along the lower edge of the screen and is able to shoot upwards the screen.
- Aliens descend in a zigzag pattern starting from the top of the screen.
- The game ends when the player kills all aliens or the aliens reach the player.
- The player scores points for every alien he destroys with the spaceship blaster, and points are shown on the scoreboard in the top-right of the screen.

Here are all other files that need to be in the same directory:
    boot.o  
    boot.S  
    COPYING  
    DE10_inpput.c  
    DE10_input.h  
    DE10_input.o  
    dtekv-lib.c  
    dtekv-lib.h  
    dtekv-lib.o  
    dtekv-script.lds  
    game.c  
    game.h  
    game.o  
    graphics.c  
    graphics.h  
    graphics.o  
    hardware_addresses.h  
    main.bin  
    main.c
    main.elf
    main.elf.txt
    main.o
    Makefile
    softfloat.a
