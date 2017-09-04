cmake_minimum_required(VERSION 3.7)
project(k5starter)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/include/freetype2/)

set(SOURCE_FILES main.cpp mainframe.cpp mainframe.h) 

add_executable(k5starter ${SOURCE_FILES})

target_link_libraries(k5starter GL GLEW glfw assimp SOIL freetype k5)

add_custom_command(TARGET k5starter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/models
        $<TARGET_FILE_DIR:k5starter>/models)

add_custom_command(TARGET k5starter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:k5starter>/shaders)

add_custom_command(TARGET k5starter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:k5starter>/textures)

add_custom_command(TARGET k5starter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/fonts
        $<TARGET_FILE_DIR:k5starter>/fonts)
