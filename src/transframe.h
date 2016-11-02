#pragma once
#include "k5.h"

class CTransFrame : public CFrame {
public:
	void Init(SDL_Renderer* rnd);
	void Cleanup();

	void Pause();
	void Resume();

	void PollEvents(CEngine* engine);
	void Loop(CEngine* engine);
	void Render(CEngine* engine);

	static CTransFrame* Instance() {
		return &m_pInstance;
	}
protected:
	CTransFrame() {}
private:
	static CTransFrame m_pInstance;

	SDL_Renderer* m_rnd;

	SDL_Surface* bkg;
	SDL_Texture* tex;
};
