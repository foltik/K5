include(Core/Sources.cmake)
include(Engine/Sources.cmake)
include(Util/Sources.cmake)

add_library(k5 SHARED ${K5_CORE_SRC} ${K5_ENGINE_SRC} ${K5_UTIL_SRC})
add_library(K5::k5 ALIAS k5)

target_compile_features(k5
    PUBLIC
        cxx_std_17)

target_include_directories(k5
    PUBLIC
        "Core"
        "Engine"
        "Util")

target_compile_options(k5
    PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:
            $<$<CONFIG:Debug>:-Wall -Wextra -Wpedantic -Wno-unused-parameter -Og -ggdb3>>
        $<$<CXX_COMPILER_ID:GNU>:
            $<$<CONFIG:Release>:-w -Ofast -ggdb3>>

        $<$<CXX_COMPILER_ID:Clang>:
            $<$<CONFIG:Debug>:-Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-missing-braces -Wno-gnu-zero-variadic-macro-arguments -fno-limit-debug-info -Og -glldb>>
        $<$<CXX_COMPILER_ID:Clang>:
            $<$<CONFIG:Release>:-w -Ofast -glldb>>

        $<$<CXX_COMPILER_ID:MSVC>:
            $<$<CONFIG:Debug>:/W3 /Od /ZI>>
        $<$<CXX_COMPILER_ID:MSVC>:
            $<$<CONFIG:Release>:/w /Ox>>)
