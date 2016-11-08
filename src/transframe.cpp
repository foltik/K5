#include "transframe.h"
#include "demoframe.h"

CTransFrame CTransFrame::pInstance;

void CTransFrame::Init(SDL_Renderer* renderer) {
	rnd = renderer;

	bkg = SDL_LoadBMP("res/test2.bmp");
	tex = SDL_CreateTextureFromSurface(rnd, bkg);
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
	SDL_RenderClear(rnd);
	SDL_RenderCopy(rnd, tex, NULL, NULL);
	SDL_RenderPresent(rnd);
}