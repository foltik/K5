#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <vector>
#include <chrono>

#define K5_EXIT_SUCCESS 0
#define K5_EXIT_FAILURE 1

class CFrame;

class CEngine {
public:
	CEngine(const GLchar* title, GLuint width, GLuint height, GLboolean fullscreen);

	bool Init();
	void Cleanup();

	void ChangeFrame(CFrame* frame);
	void PushFrame(CFrame* frame);
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
	bool running;

	std::vector<CFrame*> frames;

	static double mxpos, mypos;
	static bool keyboard[1024];

	//-----------------------------
	// Timing Vars
	//-----------------------------	
	std::chrono::duration<long long, std::nano> delta;
	std::chrono::duration<long long, std::nano> runTime;
	std::chrono::time_point<std::chrono::steady_clock> currentTime;
	std::chrono::time_point<std::chrono::steady_clock> lastTime;
	std::chrono::duration<long long, std::nano> frameTime;
	std::chrono::duration<long long, std::nano> accumulator;
	

	//-----------------------------
	// Window Data
	//-----------------------------
	const GLchar* wndTitle;
	GLuint wndW;
	GLuint wndH;
	GLboolean wndFull;
};
