#pragma once

class CEngine;

class CFrame {
public:
	virtual void Init(SDL_Renderer* rnd) = 0;
	virtual void Cleanup() = 0;
	
	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void PollEvents(CEngine* engine) = 0;
	virtual void Loop(CEngine* engine) = 0;
	virtual void Render(CEngine* engine) = 0;

	void ChangeFrame(CEngine* engine, CFrame* frame) {
		engine->ChangeFrame(frame);
	}
protected:
	CFrame(){}
};