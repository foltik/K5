#include "particle.h"

void Particle::update() {
    pos += vel;
    life -= lifeDecay;
    color += colorDecay;
    glm::clamp(color, 0.0f, 1.0f);
}

Particle::Particle(glm::vec2 position, glm::vec2 velocity, glm::vec4 col, float _life, float _lifeDecay) {
    pos = position;
    vel = velocity;
    color = col;
    colorDecay = glm::vec4(0.0f);
    life = _life;
    lifeDecay = _lifeDecay;
}

Particle::Particle(glm::vec2 position, glm::vec2 velocity, glm::vec4 col, glm::vec4 colDecay, float _life, float _lifeDecay) {
    pos = position;
    vel = velocity;
    color = col;
    colorDecay = colDecay;
    life = _life;
    lifeDecay = _lifeDecay;
}

const glm::vec2& Particle::getPos() const { return pos; }
void Particle::setPos(const glm::vec2 &pos) { Particle::pos = pos; }

const glm::vec2& Particle::getVel() const { return vel; }
void Particle::setVel(const glm::vec2 &vel) { Particle::vel = vel; }

const glm::vec4& Particle::getColor() const { return color; }
void Particle::setColor(const glm::vec4 &color) { Particle::color = color; }

const glm::vec4& Particle::getColorDecay() const { return colorDecay; }
void Particle::setColorDecay(const glm::vec4 &colorDecay) { Particle::colorDecay = colorDecay; }

float Particle::getLife() const { return life; }
void Particle::setLife(float life) { Particle::life = life; }

float Particle::getLifeDecay() const { return lifeDecay; }
void Particle::setLifeDecay(float lifeDecay) { Particle::lifeDecay = lifeDecay; }
