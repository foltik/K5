#include "FrameStack.h"

namespace k5 {
    void FrameStack::pushFrame(std::unique_ptr<k5::Frame> frame) {
        pauseTop();
        frames.push(std::move(frame));
    }

    void FrameStack::popFrame() {
        frames.pop();
        resumeTop();
    }

    void FrameStack::pauseTop() {
        if (!frames.empty())
            frames.top()->pause();
    }

    void FrameStack::resumeTop() {
        if (!frames.empty())
            frames.top()->resume();
    }
}
