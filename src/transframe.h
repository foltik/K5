#pragma once
#include "k5.h"

struct Drop {
public:
	vec2f pos;
	float vel;
	float len;
};

class CTransFrame : public CFrame {
public:
	void Init(SDL_Renderer* renderer);
	void Cleanup();

	void Pause();
	void Resume();

	void PollEvents(CEngine* engine);
	void Loop(CEngine* engine);
	void Render(CEngine* engine);

	static CTransFrame* Instance() {
		return &pInstance;
	}
protected:
	CTransFrame() {}
private:
	std::vector<Drop> drops;

	SDL_Surface* bkg;
	SDL_Texture* tex;

	SDL_Renderer* rnd;

	static CTransFrame pInstance;
};