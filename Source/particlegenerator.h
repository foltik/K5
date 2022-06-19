#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "particle.h"

class Random;
class Texture;
class Shader;

class ParticleGenerator {
public:
    ParticleGenerator(glm::mat4 projection, std::string tex, int numParticles);
    ~ParticleGenerator();

    void Tick();
    void Draw();

    void setPos(glm::vec2 position) { pos = position; }

private:
    Particle genParticle();

    Random* random;

    Shader* shader;
    Texture* texture;
    GLuint vao;
    glm::mat4 proj;

    glm::vec2 pos;

    int count;
    std::vector<Particle> particles;
};
