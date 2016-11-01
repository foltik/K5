#pragma once


//==========================================================================
//PLATFORM SPECIFIC INCLUDES
//==========================================================================
#ifdef __linux__
#include "SDL2/SDL.h"
#pragma comment(lib, "SDL2.lib")
#include "SDL2/SDL_ttf.h"
#pragma comment(lib, "SDL2_ttf.lib")
#elif _WIN32
#include <SDL2/SDL.h>
#pragma comment(lib, "SDL2.lib")
#include <SDL2/SDL_ttf.h>
#pragma comment(lib, "SDL2_ttf.lib")
#else
#error Unsupported Platform
#endif