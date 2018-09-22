#include "particlegenerator.h"

#include <glm/gtc/matrix_transform.hpp>

#include "engine.h"
#include "shader.h"
#include "texture.h"
#include "random.h"

constexpr const char* vertexSource = R"(
#version 330 Core
layout (location = 0) in vec4 vertex;
out vec2 texCoord;
out vec4 partCol;

uniform mat4 model;
uniform mat4 proj;
uniform vec4 partcolor;
uniform vec2 partpos;
uniform float partsize;

void main() {
    texCoord = vertex.zw;
    partCol = partcolor;
    gl_Position = proj * model * vec4((vertex.xy * partsize) + partpos, 0.0, 1.0);
}
)";

constexpr const char* fragmentSource = R"(
#version 330 Core
in vec2 texCoord;
in vec4 partCol;
out vec4 color;

uniform sampler2D sprite;

void main() {
    color = partCol * texture(sprite, texCoord);
}
)";

ParticleGenerator::ParticleGenerator(glm::mat4 projection, const std::string tex, int numParticles) {
    shader = new Shader(ShaderSource(vertexSource, fragmentSource));
    texture = CEngine::Instance().resourceManager().loadTexture(tex);

    random = new Random();

    proj = projection;
    count = numParticles;

    GLfloat quad[6][4] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    particles.resize((unsigned long)count);
    for (auto& particle : particles) {
        particle = genParticle();
    }
}

ParticleGenerator::~ParticleGenerator() {
    delete shader;
    delete random;
}

void ParticleGenerator::Draw() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader->Use();

    for (auto& particle : particles) {
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(particle.getPos(), 0.0f));
        shader->uMatrix4("model", model);
        shader->uMatrix4("proj", proj);
        shader->uVector2("partpos", 0.0f, 0.0f);
        shader->uVector4("partcolor", particle.getColor());
        shader->uFloat("partsize", 10.0f);
        texture->Use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::Tick() {
    for (auto& particle : particles) {
        if (particle.getLife() <= 0.0f) {
            particle = genParticle();
            continue;
        }

        particle.update();
    }
}

Particle ParticleGenerator::genParticle() {
    Particle p(glm::vec2(0.0f), glm::vec2(0.0f), glm::vec4(0.0f), glm::vec4(0.0f), 10.0f, 0.1f);
    p.setVel(glm::vec2(random->genNumber(-0.3f, 0.3f), random->genNumber(-0.3f, 0.3f)));
    p.setPos(pos);
    p.setColor(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
    p.setLife(random->genNumber(3.0f, 10.0f));
    p.setColorDecay(glm::vec4(0.0f, 0.0f, 0.0f, -1 / (p.getLife() / p.getLifeDecay())));
    return p;
}
