#include "demoframe.h"

CDemoFrame CDemoFrame::pInstance;

void CDemoFrame::Init(SDL_Renderer* renderer) {
	rnd = renderer;
	bkg = SDL_LoadBMP("res/test2.bmp");
	tex = SDL_CreateTextureFromSurface(rnd, bkg);

	vertex3f data[3] = {vec3f(-1, -1, 0), vec3f(0, 1, 0), vec3f(-1, 1, 0)};
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
			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
						if (e.type == SDL_KEYDOWN)
							engine->Quit();
						break;
					case SDLK_SPACE:
						if (e.type == SDL_KEYDOWN)
							engine->ChangeFrame(CTransFrame::Instance());
						break;
					case 'w': w = e.type == SDL_KEYDOWN; break;
					case 'a': a = e.type == SDL_KEYDOWN; break;
					case 's': s = e.type == SDL_KEYDOWN; break;
					case 'd': d = e.type == SDL_KEYDOWN; break;
				}
		}
	}
}

void CDemoFrame::Loop(CEngine* engine) {
	if (w) y--;
	if (a) x--;
	if (s) y++;
	if (d) x++;
}

void CDemoFrame::Render(CEngine* engine) {
	SDL_RenderClear(rnd);
	SDL_RenderCopy(rnd, tex, NULL, NULL);

	SDL_Rect rect = {x, y, 100, 100};
	SDL_RenderDrawRect(rnd, &rect);

	SDL_RenderPresent(rnd);
}
