#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() :
    translate(0.0f, 0.0f, 0.0f),
    rotate(0.0f, 0.0f, 0.0f, 1.0f),
    scale(1.0f, 1.0f, 1.0f) {

}

const Transform& Transform::SetParent(Transform &parent_) {
    assert(parent == nullptr);
    parent = &parent_;
    return *this;
}

const glm::mat4 &Transform::GetMatrix() {
    if (changed) {
        matrix = glm::mat4();

        glm::translate(matrix, translate);
        matrix *= glm::mat4_cast(rotate);
        glm::scale(matrix, scale);

        changed = false;
    }

    return matrix;
}
