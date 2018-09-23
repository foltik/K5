#include "CoreApp.h"

#include "Time/Time.hpp"

namespace k5 {
    CoreApp::CoreApp() {

    }

    CoreApp::~CoreApp() {

    }

    void CoreApp::launch() {
        runMainLoop = true;

        double time = 0.0;
        double delta = 0.0;

        double currentTime = 0;

        while (runMainLoop) {

        }

        // Game will exit now, remember to clean up/finish rendering!
    }

    void CoreApp::quit() {
        runMainLoop = false;
    }
}
