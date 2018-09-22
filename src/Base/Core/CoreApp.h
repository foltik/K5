#pragma once

#include "Util/Module.hpp"

namespace k5 {
    class CoreApp : public Module<CoreApp> {
    public:
        CoreApp();
        ~CoreApp() override;

    protected:
        void onStart() override;
        void onStop() override;
    };
}
