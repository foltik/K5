#pragma once
#include "k5.h"
#include "transframe.h"

class CDemoFrame : public CFrame{
public:
	void Init(SDL_Renderer* renderer);
	void Cleanup();

	void Pause();
	void Resume();

	void PollEvents(CEngine* engine);
	void Loop(CEngine* engine);
	void Render(CEngine* engine);

	static CDemoFrame* Instance() {
		return &pInstance;
	}
protected:
	CDemoFrame() {}
private:
	int x;

	SDL_Surface* bkg;
	SDL_Texture* tex;

	SDL_Renderer* rnd;

	static CDemoFrame pInstance;
};
