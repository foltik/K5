#include "renderengine.h"

#include "camera.h"
#include "light.h"
#include "shader.h"
#include "k5.h"

#include <GL/glew.h>

void RenderEngine::Render(GameObject &object) {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Forward pass
    object.Render(*forward, *this);

    // Lighting pass
    for (Light* light : lights) {
        object.Render(*light->getShader(), *this);
    }

    glfwSwapBuffers(CEngine::Instance().getWindow());
}

RenderEngine::RenderEngine() {
    //forward = new Shader("forward.vert", "forward.frag");
    forward = nullptr;
}
