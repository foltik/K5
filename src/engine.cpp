#include "engine.h"
#include "frame.h"

CEngine::CEngine(const char* title, int px, int py, int width, int height, bool fullscreen) {
	m_running = true;
	m_wndTitle = title;
	m_wndX = px;
	m_wndY = py;
	m_wndW = width;
	m_wndH = height;
	m_wndFull = fullscreen;
}

bool CEngine::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return false;
	if ((wnd = SDL_CreateWindow(m_wndTitle, m_wndX, m_wndY, m_wndW, m_wndH, m_wndFull ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN)) == NULL) return false;
	if ((rnd = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) return false;
	return true;
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