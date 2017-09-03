#include "engine.h"
#include "frame.h"

double CEngine::mxpos, CEngine::mypos;
bool CEngine::keyboard[256];
bool CEngine::mouse[16];

void CEngine::Init(std::string title, int width, int height, char* argv) {
    SetCwd(argv);
    CreateWindow(title, width, height);
}

void CEngine::CreateWindow(std::string title, int width, int height) {
	wndTitle = title;
	wndW = width;
	wndH = height;

	// Initialize GLFW and set the target version
	if (glfwInit() != GLFW_TRUE)
		throw std::runtime_error("Error//Lib: GLFW Initialization Failed");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);

	// Create and set the context as active
	wnd = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (wnd == nullptr)
		throw std::runtime_error("Error//Lib: GLFW Window Creation Failed");

	glfwMakeContextCurrent(wnd);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Error//Lib: GLEW Initialization Failed\n");

	// Retrieve the frame buffer size and create the OpenGL viewport accordingly
	int fbWidth, fbHeight;
	glfwGetFramebufferSize(wnd, &fbWidth, &fbHeight);
	glViewport(0, 0, fbWidth, fbHeight);

	// Initialize starting time so the first tick doesn't last forever
	lastTime = std::chrono::steady_clock::now();
	currentTime = std::chrono::steady_clock::now();

	// Key Callbacks
	glfwSetKeyCallback(wnd, key_callback);
	glfwSetCursorPosCallback(wnd, mouse_callback);
	glfwSetMouseButtonCallback(wnd, mousebutton_callback);
	glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // TODO: Might need this for text rendering functions, move to init there
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void CEngine::SetCwd(char* argv) {
    std::string s(argv);
    s = s.substr(0, s.find_last_of('/') + 1);
    cwd = s;
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

void CEngine::mousebutton_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS)
		mouse[button] = true;
	else if (action == GLFW_RELEASE)
		mouse[button] = false;
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
	frames.top()->ProcessInput(keyboard, mouse, mxpos, mypos);
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
