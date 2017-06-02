#include "engine.h"

#include "frame.h"

GLuint CEngine::wndH;
GLuint CEngine::wndW;

double CEngine::mxpos;
double CEngine::mypos;

bool CEngine::keyboard[1024];

void CEngine::CreateWindow(const GLchar* title, GLuint width, GLuint height, GLboolean fullscreen) {
	wndTitle = title;
	wndW = width;
	wndH = height;
	wndFull = fullscreen;

	// Initialize GLFW and set the target version
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

	// Create and set the context as active
	wnd = glfwCreateWindow(wndW, wndH, wndTitle, wndFull ? mon : nullptr, nullptr);
	if (wnd == nullptr)
		throw new std::runtime_error("Error//Lib: GLFW Window Creation Failed");

	glfwMakeContextCurrent(wnd);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw new std::runtime_error("Error//Lib: GLEW Initialization Failed\n");

	// Retrieve the window size and create the OpenGL viewport accordingly
	int w, h;
	glfwGetFramebufferSize(wnd, &w, &h);
	glViewport(0, 0, width, height);

	// Initialize starting time so the first tick doesn't last forever
	lastTime = std::chrono::steady_clock::now();
	currentTime = std::chrono::steady_clock::now();

	// Key Callbacks
	glfwSetKeyCallback(wnd, key_callback);
	glfwSetCursorPosCallback(wnd, mouse_callback);
	glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void CEngine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS)
		keyboard[key] = true;
	else if (action == GLFW_RELEASE)
		keyboard[key] = false;
}

void CEngine::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	mxpos = xpos;
	mypos = ypos;
}

void CEngine::Tick() {
	// Get frame time
	currentTime = std::chrono::steady_clock::now();
	frameTime = currentTime - lastTime; 
	lastTime = std::chrono::steady_clock::now();

	accumulator += frameTime;

	while (accumulator > delta) {
		ProcessInput();
		Loop();
		accumulator -= delta;
		runTime += delta;
	}

	glfwPollEvents();
	Render();
}

void CEngine::ProcessInput() {
	frames.top()->ProcessInput(keyboard, mxpos, mypos);
}

void CEngine::Loop() {
	frames.top()->Loop();
}

void CEngine::Render() {
	frames.top()->Render();
}

void CEngine::Cleanup() {
	while (!frames.empty()) {
		frames.top()->Cleanup();
		frames.pop();
	}

	glfwTerminate();
}

void CEngine::ChangeFrame(IFrame* frame) {
	if (!frames.empty()) {
		frames.top()->Cleanup();
		frames.pop();
	}

	frames.push(frame);
	frames.top()->Init(this);
}

void CEngine::PushFrame(IFrame* frame) {
	if (!frames.empty()) 
		frames.top()->Pause();

	frames.push(frame);
	frames.top()->Init(this);
}

void CEngine::PopFrame() {
	if (!frames.empty()) {
		frames.top()->Cleanup();
		frames.pop();
	}

	if (!frames.empty()) 
		frames.top()->Resume();
}
