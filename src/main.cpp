#include "main.h"

#undef main // Remove SDL's definition of main to SDL_main
int main() {
	CEngine game("K5 Engine Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, true);

	if (!game.Init()) return K5_EXIT_FAILURE;

	game.ChangeFrame(CDemoFrame::Instance());

	while (game.Running()) {
		game.PollEvents();
		game.Loop();
		game.Render();
	}

	game.Cleanup();

	return K5_EXIT_SUCCESS;
}