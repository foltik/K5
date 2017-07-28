cmake_minimum_required(VERSION 3.7)
project(k5)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/include/freetype2/)

set(SOURCE_FILES
        src/camera.cpp
        src/camera.h
        src/engine.cpp
        src/engine.h
        src/frame.h
        src/k5.h
        src/mesh.cpp
        src/mesh.h
        src/model.cpp
        src/model.h
        src/shader.cpp
        src/shader.h
        src/textrenderer.cpp
        src/textrenderer.h
        src/texture.cpp
        src/texture.h
        src/spriterenderer.cpp
        src/spriterenderer.h
        src/cubemap.cpp
        src/cubemap.h
        src/particle.cpp
        src/particle.h
        src/particlegenerator.cpp
        src/particlegenerator.h)

add_library(k5 STATIC ${SOURCE_FILES})

set_target_properties(k5 PROPERTIES
                      PUBLIC_HEADER "src/camera.h;src/engine.h;src/frame.h;src/k5.h;src/mesh.h;src/model.h;src/shader.h;src/textrenderer.h;src/texture.h;src/cubemap.h;src/spriterenderer.h;src/particle.h;src/particlegenerator.h")

install(TARGETS k5
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/k5)
