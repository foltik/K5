#pragma once

class CEngine;

class IFrame {
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void ProcessInput(bool keyboard[512], bool mouse[16], double mxpos, double mypos) = 0;
	virtual void Loop() = 0;
	virtual void Render() = 0;
protected:
	IFrame() = default;

	CEngine* engine;
};
