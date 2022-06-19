cmake_minimum_required(VERSION 3.9)
project(TestApp)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    main.cpp
        MainFrame.cpp
        MainFrame.h)

add_executable(TestApp ${SOURCE_FILES})

target_link_libraries(TestApp k5)
