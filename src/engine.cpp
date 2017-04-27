#include "engine.h"

#include "frame.h"

CEngine::CEngine(const char* title, unsigned int px, unsigned int py, unsigned int width, unsigned int height, bool fullscreen) {
	running = true;
	wndTitle = title;
	wndX = px;
	wndY = py;
	wndW = width;
	wndH = height;
	wndFull = fullscreen;
}

bool CEngine::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return false;
	if ((wnd = SDL_CreateWindow(wndTitle, wndX, wndY, wndW, wndH, wndFull ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN)) == NULL) return false;
	if ((rnd = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) return false;

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_FRAMEBUFFER_SRGB);

	// Initialize Timing Vars
	time = 0.0;
	lastTime = SDL_GetTicks() / 1000.0;
	accumulator = 0.0;

	return true;
}

void CEngine::Tick() {
	double currentTime = SDL_GetTicks() / 1000.0;
	double frameTime = currentTime - lastTime;
	lastTime = currentTime;

	accumulator += frameTime;

	while (accumulator > delta) {
		PollEvents();
		Loop();
		accumulator -= delta;
		time += delta;
	}

	Render();
}

void CEngine::PollEvents() {
	frames.back()->PollEvents(this);
}

void CEngine::Loop() {
	frames.back()->Loop(this);
}

void CEngine::Render() {
	frames.back()->Render(this);
}

void CEngine::Cleanup() {
	while (!frames.empty()) {
		frames.back()->Cleanup();
		frames.pop_back();
	}
	SDL_Quit();
}

void CEngine::ChangeFrame(CFrame* frame) {
	if (!frames.empty()) {
		frames.back()->Cleanup();
		frames.pop_back();
	}

	frames.push_back(frame);
	frames.back()->Init(rnd);
}

void CEngine::PushFrame(CFrame* frame) {
	if (!frames.empty()) frames.back()->Pause();

	frames.push_back(frame);
	frames.back()->Init(rnd);
}

void CEngine::PopFrame() {
	if (!frames.empty()) {
		frames.back()->Cleanup();
		frames.pop_back();
	}

	if (!frames.empty()) frames.back()->Resume();
}
