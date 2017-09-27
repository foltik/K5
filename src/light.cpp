#include "light.h"

#include "shader.h"

Light::Light(glm::vec3 _color, float _intensity) : color(_color) {
    intensity = _intensity;
}

Light::~Light() {
    delete shader;
}

const glm::vec3 &Light::getColor() const {
    return color;
}

void Light::setColor(const glm::vec3 &color) {
    Light::color = color;
}

float Light::getIntensity() const {
    return intensity;
}

void Light::setIntensity(float intensity) {
    Light::intensity = intensity;
}

Shader *Light::getShader() const {
    return shader;
}

void Light::setShader(Shader *shader) {
    Light::shader = shader;
}

