cmake_minimum_required(VERSION 3.7)
project(k5)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(/usr/include/freetype2/)

set(SOURCE_FILES
        src/camera.cpp
        src/camera.h
        src/engine.cpp
        src/engine.h
        src/frame.h
        src/k5.h
        src/model.h
        src/model.cpp
        src/shader.cpp
        src/shader.h
        src/textrenderer.cpp
        src/textrenderer.h
        src/texture.h
        src/spriterenderer.cpp
        src/spriterenderer.h
        src/cubemap.cpp
        src/cubemap.h
        src/particle.cpp
        src/particle.h
        src/particlegenerator.cpp
        src/particlegenerator.h
        src/random.h
        src/resourcemanager.h
        src/resourcemanager.cpp
        src/gameobject.h
        src/gameobject.cpp
        src/transform.cpp
        src/transform.h
        src/gamecomponent.h
        src/renderengine.cpp
        src/renderengine.h
        src/light.cpp
        src/light.h
        src/modelrenderer.cpp
        src/modelrenderer.h)

add_library(k5 STATIC ${SOURCE_FILES})

set_target_properties(k5 PROPERTIES
                      PUBLIC_HEADER "src/camera.h;src/engine.h;src/frame.h;src/k5.h;src/model.h;src/shader.h;src/textrenderer.h;src/texture.h;src/cubemap.h;src/spriterenderer.h;src/particle.h;src/particlegenerator.h;src/random.h;src/resourcemanager.h;src/gameobject.h;src/transform.h;src/gamecomponent.h;src/renderengine.h;src/light.h")

install(TARGETS k5
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/k5)
