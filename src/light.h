#pragma once
#include <glm/glm.hpp>

#include "gamecomponent.h"

class Light : public GameComponent {
    glm::vec3 color;
};
