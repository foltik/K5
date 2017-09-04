#include <k5/k5.h>

#include "mainframe.h"

int main(int argc, char** argv) {
    CEngine& game = CEngine::Instance();

	game.Init("k5starter", 800, 600, argv[0]);
    game.ChangeFrame(&MainFrame::Instance());
	game.Launch();
	
	return 0;
}
