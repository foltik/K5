#pragma once
#ifdef __linux__
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#elif _WIN32
#include <SDL2/SDL.h>
#pragma comment(lib, "SDL2.lib")
#include <SDL2/SDL_ttf.h>
#pragma comment(lib, "SDL2_ttf.lib")

#else
#error Unsupported Platform
#endif

#include <cstdint>
#include <vector>

#define FRAME_CAP 240
#define FRAME_TIME 1.0 / FRAME_CAP

#define K5_EXIT_SUCCESS 0
#define K5_EXIT_FAILURE 1

typedef int_fast64_t int64;
typedef uint_fast64_t uint64;
typedef int_fast32_t int32;
typedef uint_fast32_t uint32;

class CFrame;

class CEngine {
public:
	CEngine(const char* title, uint32 px, uint32 py, uint32 width, uint32 height, bool fullscreen);

	bool Init();
	void Cleanup();

	void ChangeFrame(CFrame* frame);
	void PushFrame(CFrame* frame);
	void PopFrame();

	void Tick();

	void PollEvents();
	void Loop();
	void Render();

	SDL_Window* wnd;
	SDL_Renderer* rnd;

	bool Running() { return running; }
	void Quit() { running = false; }
private:
	bool running;

	std::vector<CFrame*> frames;

	//-----------------------------
	// Timing Vars
	//-----------------------------	
	bool doRender;
	int32 lastTime = 0;
	int32 startTime = 0;
	int32 frameCount = 0;
	int32 fps = 0;
	double remainingTime = 0;

	//-----------------------------
	// Window Data
	//-----------------------------
	const char* wndTitle;
	uint32 wndX;
	uint32 wndY;
	uint32 wndW;
	uint32 wndH;
	bool wndFull;
};
