#pragma once

#include "Util/Assert.hpp"

#include <utility>

namespace k5 {
    template<typename T>
    class Module {
    public:
        static T& instance() {
            K5_ASSERT(started() && !stopped(), "Tried to get instance from stopped module")

            return *_instance();
        }

        static T* pInstance() {
            if (!started())
                ;// uh-oh

            if (stopped())
                ;// uh-oh

            return _instance();
        }

        template<typename... Args>
        static void start(Args&&... args) {
            if (started())
                ;//uh-oh

            _instance() = new T(std::forward<Args>(args)...);
            started() = true;

            dynamic_cast<Module*>(_instance())->onStart();
        }

        static void stop() {
            if (stopped())
                ;//uh-oh

            if (!started())
                ;//uh-oh

            dynamic_cast<Module*>(_instance())->onStop();

            delete _instance();
            stopped() = true;
        }

        Module(Module&&) = delete;
        Module& operator=(Module&&) = delete;
        Module(const Module&) = delete;
        Module& operator=(const Module&) = delete;

    protected:
        Module() = default;
        virtual ~Module() = default;

        virtual void onStart() {};
        virtual void onStop() {};

    private:
        static T*& _instance() {
            static T* instance = nullptr;
            return instance;
        }

        static bool& started() {
            static bool instance = false;
            return instance;
        }

        static bool& stopped() {
            static bool instance = false;
            return instance;
        }
    };
}
