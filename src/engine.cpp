#include "engine.h"

#include "frame.h"

CEngine::CEngine(GLchar* title, GLuint width, GLuint height, GLboolean fullscreen) {
	// Set the required local variables to initialize everything later in Init();
	running = true;
	wndTitle = title;
	wndW = width;
	wndH = height;
	wndFull = fullscreen;
}

bool CEngine::Init() {
	printf("Starting OpenGL 3.3 Context\n");

	// Initialize GLFW and set the target version
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create and set the context as active
	wnd = glfwCreateWindow(wndW, wndH, wndTitle, wndFull ? mon : NULL, NULL);
	if (wnd == NULL) {
		printf("GLFW Window Creation Failed\n");
		return false;
	}
	glfwMakeContextCurrent(wnd);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		printf("GLEW Initialization Failed\n");
		return false;
	}

	// Retrieve the window size and create the OpenGL viewport accordingly
	int width, height;
	glfwGetFramebufferSize(wnd, &width, &height);
	glViewport(0, 0, width, height);

	// Initialize Timing Vars
	delta = std::chrono::duration<long long, std::nano>(16666667);
	accumulator = std::chrono::duration<long long, std::nano>(0);
	currentTime = std::chrono::steady_clock::now();
	lastTime = std::chrono::steady_clock::now();

	return true;
}

void CEngine::Tick() {
	// Get frame time
	currentTime = std::chrono::steady_clock::now();
	frameTime = currentTime - lastTime; 
	lastTime = std::chrono::steady_clock::now();

	accumulator += frameTime;

	while (accumulator > delta) {
		PollEvents();
		Loop();
		accumulator -= delta;
		runTime += delta;
	}

	Render();
}

void CEngine::PollEvents() {
	frames.back()->PollEvents();
}

void CEngine::Loop() {
	frames.back()->Loop();
}

void CEngine::Render() {
	frames.back()->Render();
}

void CEngine::Cleanup() {
	while (!frames.empty()) {
		frames.back()->Cleanup();
		frames.pop_back();
	}
	glfwTerminate();
}

void CEngine::ChangeFrame(CFrame* frame) {
	if (!frames.empty()) {
		frames.back()->Cleanup();
		frames.pop_back();
	}

	frames.push_back(frame);
	frames.back()->Init();
}

void CEngine::PushFrame(CFrame* frame) {
	if (!frames.empty()) frames.back()->Pause();

	frames.push_back(frame);
	frames.back()->Init();
}

void CEngine::PopFrame() {
	if (!frames.empty()) {
		frames.back()->Cleanup();
		frames.pop_back();
	}

	if (!frames.empty()) frames.back()->Resume();
}
