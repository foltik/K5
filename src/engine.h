#pragma once
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

#include <vector>

#define K5_EXIT_SUCCESS 0
#define K5_EXIT_FAILURE 1

class CFrame;

class CEngine {
public:
	CEngine(const char* title, int px, int py, int width, int height, bool fullscreen);

	bool Init();
	void Cleanup();

	void ChangeFrame(CFrame* frame);
	void PushFrame(CFrame* frame);
	void PopFrame();

	void PollEvents();
	void Loop();
	void Render();

	SDL_Window* wnd;
	SDL_Renderer* rnd;

	bool Running() { return m_running; }
	void Quit() { m_running = false; }
private:
	std::vector<CFrame*> frames;
	bool m_running;

	const char* m_wndTitle;
	int m_wndX;
	int m_wndY;
	int m_wndW;
	int m_wndH;
	bool m_wndFull;
};