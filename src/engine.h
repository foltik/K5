#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stack>
#include <chrono>

#include "resourcemanager.h"

class IFrame;

class CEngine {
public:
	static CEngine& Instance() {
		static CEngine engine;
		return engine;
	}

    CEngine(const CEngine&) = delete;
	CEngine(CEngine&&) = delete;
	void operator=(const CEngine&) = delete;
	void operator=(CEngine&&) = delete;


	void ChangeFrame(IFrame* frame);
	void PushFrame(IFrame* frame);
	void PopFrame();

    void Init(std::string title, int width, int height, char* cwd);
    void Launch();
    void Quit() { running = false; }

    std::string getCwd() const { return cwd; }

    int getWindowWidth() const { return wndW; }
    int getWindowHeight() const { return wndH; }

    void disableCursor() { glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
    void enableCursor() { glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

    ResourceManager& resourceManager() { return resManager; }

protected:
    CEngine() = default;

private:
    void CreateWindow(std::string title, int width, int height);

	void Tick();

	void ProcessInput();
	void Loop();
	void Render();

    void Cleanup();

    ResourceManager resManager = ResourceManager();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void mousebutton_callback(GLFWwindow* window, int button, int action, int mods);


	GLFWwindow* wnd = nullptr;
	int wndW = 0;
	int wndH = 0;
    std::string wndTitle = "";
    std::string cwd = "";


	std::stack<IFrame*> frames;


	static double mxpos, mypos;
	static bool keyboard[512];
	static bool mouse[16];


	typedef std::chrono::duration<long long, std::nano> duration_t;
	typedef std::chrono::time_point<std::chrono::steady_clock> timepoint_t;

    bool firstTick = true;
	bool running = false;

	timepoint_t currentTime;
	timepoint_t lastTime;
	duration_t frameTime = duration_t(0);
	duration_t delta = duration_t(16666667);
	duration_t accumulator = duration_t(0);
	duration_t runTime = duration_t(0);
};
