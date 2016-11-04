#include "main.h"

#undef main // Undefine SDL's definition of 'main' (It is defined as SDL_main)
int main() {
	CEngine game("K5 Engine Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1600, 900, false);

	// Initialize Engine
	if (!game.Init()) return K5_EXIT_FAILURE;

	// Set Initial Frame
	game.ChangeFrame(CDemoFrame::Instance());

	while (game.Running()) 
		game.Tick();
	game.Cleanup();

	return K5_EXIT_SUCCESS;
}
