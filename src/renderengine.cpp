#include "renderengine.h"

#include "camera.h"
#include "light.h"
#include "shader.h"
#include "k5.h"
#include "transform.h"

#include <GL/glew.h>
#include <string>

RenderEngine::~RenderEngine() {
    delete ambient;
}

void RenderEngine::Init() {
    ambient = new Shader("shaders/ambient.vert", "shaders/ambient.frag");
}

void RenderEngine::Render(GameObject &object) {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Ambient pass
    ambient->uMatrix4("viewproj", currentCamera->GetViewProjection());
    ambient->uVector3("ambient", 0.2f, 0.2f, 0.2f);
    object.Render(*ambient, *this);

    // Lighting pass
    for (Light* light : lights) {
        object.Render(*light->getShader(), *this);
    }

    glfwSwapBuffers(CEngine::Instance().getWindow());
}

void RenderEngine::SetCamera(Camera* camera) {
    currentCamera = camera;
}

