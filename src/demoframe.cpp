#include "demoframe.h"

CDemoFrame CDemoFrame::m_pInstance;

void CDemoFrame::Init(SDL_Renderer* rnd) {
	m_rnd = rnd;

	bkg = SDL_LoadBMP("test.bmp");
	tex = SDL_CreateTextureFromSurface(m_rnd, bkg);
}

void CDemoFrame::Cleanup() {
	SDL_FreeSurface(bkg);
	SDL_DestroyTexture(tex);
}

void CDemoFrame::Pause() {}
void CDemoFrame::Resume() {}

void CDemoFrame::PollEvents(CEngine* engine) {
	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			engine->Quit();
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
					engine->Quit();
					break;
			}
		}
	}
}

void CDemoFrame::Loop(CEngine* engine) {}

void CDemoFrame::Render(CEngine* engine) {
	SDL_RenderClear(m_rnd);
	SDL_RenderCopy(m_rnd, tex, NULL, NULL);
	SDL_RenderPresent(m_rnd);
	SDL_Delay(10);
}