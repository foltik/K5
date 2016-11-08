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

#include <vector>

#include "vec2f.h"
#include "vec3f.h"

#define FRAME_CAP 240
#define FRAME_TIME 1.0 / FRAME_CAP

#define K5_EXIT_SUCCESS 0
#define K5_EXIT_FAILURE 1

class CFrame;

class CEngine {
public:
	CEngine(const char* title, unsigned int px, unsigned int py, unsigned int width, unsigned int height, bool fullscreen);

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
	const double delta = 1.0 / 60.0;
	double time;
	double lastTime;
	double accumulator;

	//-----------------------------
	// Window Data
	//-----------------------------
	const char* wndTitle;
	unsigned int wndX;
	unsigned int wndY;
	unsigned int wndW;
	unsigned int wndH;
	bool wndFull;
};
