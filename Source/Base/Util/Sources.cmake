set(K5_UTIL_BASE_INC
    "Util/Util/Module.hpp")

set(K5_UTIL_FRAME_INC
    "Util/Frame/Frame.h"
    "Util/Frame/FrameStack.h")

set(K5_UTIL_FRAME_SRC
    "Util/Frame/FrameStack.cpp")

set(K5_UTIL_TIME_INC
    "Util/Time/Time.hpp")

set(K5_UTIL_SRC
    ${K5_UTIL_UTIL_INC}
    ${K5_UTIL_FRAME_INC}
    ${K5_UTIL_FRAME_SRC}
    ${K5_UTIL_TIME_SRC})