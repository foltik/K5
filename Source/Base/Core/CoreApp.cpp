#include "CoreApp.h"

#include "Time/Time.hpp"

namespace k5 {
    CoreApp::CoreApp() {

    }

    CoreApp::~CoreApp() {

    }

    void CoreApp::launch() {
        runMainLoop = true;

        Time::nanoseconds time(0);
        Time::nanoseconds delta(16666667);

        auto currentTime = Time::currentTime();
        Time::nanoseconds accumulator(0);

        while (runMainLoop) {
            auto newTime = Time::currentTime();
            auto frameTime = newTime - currentTime;
            currentTime = newTime;

            accumulator += frameTime;

            while (accumulator >= delta) {
                
                
                time += delta;
                accumulator -= delta;
            }

            // for physics lerp
            double alpha = accumulator / delta;

            // render
        }

        // Game will exit now, remember to clean up/finish rendering!
    }

    void CoreApp::quit() {
        runMainLoop = false;
    }
}
