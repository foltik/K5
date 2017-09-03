#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdexcept>
#include <cstdio>
#include <stack>
#include <chrono>

class IFrame;

class CEngine {
public:
	static CEngine& Instance() {
		static CEngine engine;
		return engine;
	}

    void Init(std::string title, int width, int height, char* cwd);


    std::string getCwd() const { return cwd; }

    int getWindowWidth() const { return wndW; }
    int getWindowHeight() const { return wndH; }

    void CreateWindow(std::string title, int width, int height);

	void Cleanup();

	void ChangeFrame(IFrame* frame);
	void PushFrame(IFrame* frame);
	void PopFrame();

	void Tick();

	void ProcessInput();
	void Loop();
	void Render();

    void SetCwd(char* argv);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void mousebutton_callback(GLFWwindow* window, int button, int action, int mods);

	GLFWwindow* wnd = nullptr;
	int wndW = 0;
	int wndH = 0;
    std::string wndTitle = "";
    std::string cwd = "";

	bool Running() { return running; }
	void Quit() { running = false; }

protected:
	CEngine() { running = true; }
	CEngine(const CEngine&) = delete;
	CEngine(CEngine&&) = delete;
	void operator=(const CEngine&) = delete;
	void operator=(CEngine&&) = delete;

private:
	bool running;

	std::stack<IFrame*> frames;

	static double mxpos, mypos;
	static bool keyboard[256];
	static bool mouse[16];

	typedef std::chrono::duration<long long, std::nano> duration_t;
	typedef std::chrono::time_point<std::chrono::steady_clock> timepoint_t;
	
	timepoint_t currentTime;
	timepoint_t lastTime;
	duration_t frameTime;

	duration_t delta = duration_t(16666667);
	duration_t accumulator = duration_t(0);
	duration_t runTime = duration_t(0);
};
