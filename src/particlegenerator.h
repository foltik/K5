#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <random>

#include "particle.h"

class Texture;
class Shader;

// TODO: FIX THIS HOLY CRAP
template <typename T>
class Variance {
public:
    T generate() {
        return ((float)rand() / (float)(RAND_MAX / (max - min))) + min;
    }
    T min;
    T max;
};

class ParticleGenerator {
public:
    ParticleGenerator(glm::mat4 projection, const std::string tex, int numParticles);
    ~ParticleGenerator();

    void Tick();
    void Draw();

    void setPos(glm::vec2 position) { pos = position; }

private:
    Particle genParticle();

    Shader* shader;
    Texture* texture;
    GLuint vao;
    glm::mat4 proj;

    glm::vec2 pos;

    int count;
    std::vector<Particle> particles;

    Variance<float> lifeVar;
    glm::vec2 posVar;
    glm::vec2 velVar;//Variance<glm::vec2> velVar;
    glm::vec4 colorVar;//Variance<glm::vec4> colorVar;
};
