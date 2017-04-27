#include "transframe.h"
#include "demoframe.h"

CTransFrame CTransFrame::pInstance;

void CTransFrame::Init(SDL_Renderer* renderer) {
	rnd = renderer;
	
	for (int i = 0; i < 500; i++) {
		Drop d;
		d.pos.x = rand() % 1600 + 1;
		d.pos.y = rand() % 900 + 1;
		d.vel = rand() % 4 + 2;
		d.len = rand() % 10 + 5;
		drops.push_back(d);
	}
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

void CTransFrame::Loop(CEngine* engine) {
	for (int i = 0; i < drops.size(); i++) {
		if (drops[i].pos.y < 900)
			drops[i].pos.y += drops[i].vel;
		else
			drops[i].pos.y = -10;
	}
}

void CTransFrame::Render(CEngine* engine) {
	SDL_SetRenderDrawColor(rnd, 230, 230, 250, 255);
	SDL_RenderClear(rnd);

	for (Drop d : drops) {
		SDL_SetRenderDrawColor(rnd, 138, 143, 226, 255);
		SDL_RenderDrawLine(rnd, d.pos.x, d.pos.y, d.pos.x, d.pos.y + d.len);
	}

	SDL_RenderPresent(rnd);
}