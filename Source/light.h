#pragma once
#include <glm/glm.hpp>

#include "gamecomponent.h"

class Light : public GameComponent {
public:
    Light(glm::vec3 _color, float _intensity);
    ~Light();

private:
    glm::vec3 color;
public:
    const glm::vec3 &getColor() const;
    void setColor(const glm::vec3 &color);

    float getIntensity() const;
    void setIntensity(float intensity);

    Shader *getShader() const;
    void setShader(Shader *shader);

private:
    float intensity;

    Shader* shader;
};
