#pragma once
#include <vector>

#include "gameobject.h"

class Camera;
class Light;

class RenderEngine {
public:
    RenderEngine();

    void Render(GameObject& object);

private:
    std::vector<Camera*> cameras;
    std::vector<Light*> lights;
};
