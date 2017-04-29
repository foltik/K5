#pragma once

class CEngine;

class CFrame {
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void ProcessInput(bool* keyboard) = 0;
	virtual void Loop() = 0;
	virtual void Render() = 0;

	void ChangeFrame(CFrame* frame) {
		engine->ChangeFrame(frame);
	}

	void SetEngine(CEngine* e) {
		engine = e;
	}
protected:
	CFrame() {}

	CEngine* engine;
};