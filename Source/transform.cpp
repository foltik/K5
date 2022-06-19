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

void Transform::LookAt(glm::vec3 pos, glm::vec3 up) {
    // TODO: write this function
}

glm::vec3 Transform::Front() const {
    glm::vec3 euler = glm::eulerAngles(rotate);

    glm::vec3 front;
    front.x = glm::cos(glm::radians(euler.y)) * glm::cos(glm::radians(euler.x));
    front.y = glm::sin(glm::radians(euler.y));
    front.z = glm::cos(glm::radians(euler.y)) * glm::sin(glm::radians(euler.x));

    return front;
}

const glm::mat4& Transform::GetMatrix() {
    if (changed) {
        matrix = glm::mat4();

        glm::translate(matrix, translate);
        matrix *= glm::mat4_cast(rotate);
        glm::scale(matrix, scale);

        changed = false;
    }

    return matrix;
}

const glm::vec3& Transform::GetTranslate() const {
    return translate;
}

void Transform::SetTranslate(const glm::vec3& translate) {
    Transform::translate = translate;
}

const glm::quat& Transform::GetRotate() const {
    return rotate;
}

void Transform::SetRotate(const glm::quat& rotate) {
    Transform::rotate = rotate;
}

const glm::vec3 &Transform::GetScale() const {
    return scale;
}

void Transform::SetScale(const glm::vec3 &scale) {
    Transform::scale = scale;
}
