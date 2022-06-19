#pragma once
#include <vector>

#include "gameobject.h"

class Camera;
class Light;
class Shader;

class RenderEngine {
public:
    RenderEngine() = default;
    ~RenderEngine();
    void Init();

    void Render(GameObject& object);

    void SetCamera(Camera* camera);

private:
    std::vector<Camera*> cameras;
    Camera* currentCamera;

    std::vector<Light*> lights;

    Shader* ambient;
};
