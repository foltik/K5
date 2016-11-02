#include "transframe.h"
#include "demoframe.h"

CTransFrame CTransFrame::m_pInstance;

void CTransFrame::Init(SDL_Renderer* rnd) {
	m_rnd = rnd;

	bkg = SDL_LoadBMP("res/test2.bmp");
	tex = SDL_CreateTextureFromSurface(m_rnd, bkg);
}

void CTransFrame::Cleanup() {
	SDL_FreeSurface(bkg);
	SDL_DestroyTexture(tex);
}

void CTransFrame::Pause() {}
void CTransFrame::Resume() {}

void CTransFrame::PollEvents(CEngine* engine) {
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
			case SDLK_SPACE:
					engine->ChangeFrame(CDemoFrame::Instance());
					break;
			}
		}
	}
}

void CTransFrame::Loop(CEngine* engine) {}

void CTransFrame::Render(CEngine* engine) {
	SDL_RenderClear(m_rnd);
	SDL_RenderCopy(m_rnd, tex, NULL, NULL);
	SDL_RenderPresent(m_rnd);
	SDL_Delay(10);
}
