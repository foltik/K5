#include "mainframe.h"
    
void MainFrame::Init() {}
void MainFrame::Cleanup() {}

void MainFrame::Pause() {}
void MainFrame::Resume() {}

void MainFrame::ProcessInput(bool *keyboard, bool *mouse, double mxpos, double mypos) {
    if (keyboard[GLFW_KEY_ESCAPE])
		CEngine::Instance().Quit();
}

void MainFrame::Loop() {}

void MainFrame::Render() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
