#include "MainFrame.h"
#include "CoreApp.h"

int main(int argc, char** argv) {
	k5::CoreApp app;
	app.emplaceFrame<MainFrame>();

	return 0;
}
