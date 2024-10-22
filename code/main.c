#include <lib.h>

#include "game.c"

void main()
{
    initRomFct();
    initRand(12);
	// TEXTMODE();
    kernelInit();
    osmeInit();



    // PRINTS(4,12,"Enter your name : ");
    // INPUTS(12, 4+18, 10, gameData.name);
    // PRINTS(4,14,"Your name is: ");
    // PRINTS(4+15,14,gameData.name);

	gameInit();
	while(1){
		lsys();
		gamePulse();
	}
	// // Load the first picture at the default address specified in the script
	// LoadFileAt(LOADER_PICTURE_FIRSTPROGRAM,0xa000);

	// // Quit and return to the loader
	// InitializeFileAt(LOADER_PROGRAM_SECOND,0x400);
}
