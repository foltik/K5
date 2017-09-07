#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
public:
    Transform();

    const Transform& SetParent(Transform& parent_);

    const glm::mat4& GetMatrix();

private:
    glm::vec3 translate;
    glm::quat rotate;
    glm::vec3 scale;

    glm::mat4 matrix;

    bool changed = true;

    Transform* parent = nullptr;
};