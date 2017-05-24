#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <cstdio>
#include <stack>
#include <chrono>

#define K5_EXIT_SUCCESS 0
#define K5_EXIT_FAILURE 1

class IFrame;

class CEngine {
public:
	static CEngine& Instance() {
		static CEngine engine;
		return engine;
	}

	void CreateWindow(const GLchar* title, GLuint width, GLuint height, GLboolean fullscreen);

	bool Init();
	void Cleanup();

	void ChangeFrame(IFrame* frame);
	void PushFrame(IFrame* frame);
	void PopFrame();

	void Tick();

	void ProcessInput();
	void Loop();
	void Render();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	GLFWmonitor* mon;
	GLFWwindow* wnd;

	bool Running() { return running; }
	void Quit() { running = false; }

private:
	CEngine();

	// Prevent copies
	CEngine(const CEngine&) = delete;
	CEngine(CEngine&&) = delete;	
	void operator=(const CEngine&) = delete;
	void operator=(CEngine&&) = delete;

	bool running;

	std::stack<IFrame*> frames;

	static double mxpos, mypos;
	static bool keyboard[1024];

	typedef std::chrono::duration<long long, std::nano> duration_t;
	typedef std::chrono::time_point<std::chrono::steady_clock> timepoint_t;
	
	timepoint_t currentTime;
	timepoint_t lastTime;
	duration_t frameTime;

	duration_t delta = duration_t(16666667);
	duration_t accumulator = duration_t(0);
	duration_t runTime = duration_t(0);


	//-----------------------------
	// Window Data
	//-----------------------------
	const GLchar* wndTitle;
	GLuint wndW;
	GLuint wndH;
	GLboolean wndFull;
};
