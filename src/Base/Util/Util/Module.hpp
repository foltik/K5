//
// Created by Jack Foltz on 9/22/18.
//

#pragma once

namespace k5 {
    template<typename T>
    class Module {
    public:
        static T& instance() {
            if (!started())
                ;// uh-oh

            if (stopped())
                ;// uh-oh

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

    protected:
        Module() = default;
        virtual ~Module() = default;

        Module(Module&&) = delete;
        Module& operator=(Module&&) = delete;
        Module(const Module&) = delete;
        Module& operator=(const Module&) = delete;

        virtual void onStart() = 0;
        virtual void onStop() = 0;

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
