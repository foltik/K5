#pragma once

#include <atomic>
#include "Frame/FrameStack.h"

namespace k5 {
    class CoreApp : public FrameStack {
    public:
        CoreApp();
        virtual ~CoreApp();

        void launch();
        void quit();

    private:
        std::atomic_bool runMainLoop = false;
    };
}
