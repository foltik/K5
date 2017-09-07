#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform {
public:
    Transform();
    const Transform& SetParent(Transform& parent_);

    const glm::vec3& GetTranslate() const;
    void SetTranslate(const glm::vec3& translate);
    const glm::quat& GetRotate() const;
    void SetRotate(const glm::quat& rotate);
    const glm::vec3& GetScale() const;
    void SetScale(const glm::vec3& scale);

    void LookAt(glm::vec3 pos, glm::vec3 up);

    glm::vec3 Front() const;

    const glm::mat4& GetMatrix();

private:
    glm::vec3 translate;
    glm::quat rotate;
    glm::vec3 scale;

    glm::mat4 matrix;

    bool changed = true;

    Transform* parent = nullptr;
};