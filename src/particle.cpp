#include "particle.h"

const glm::vec2& Particle::getPos() const { return pos; }
void Particle::setPos(const glm::vec2 &pos) { Particle::pos = pos; }

const glm::vec2& Particle::getVel() const { return vel; }
void Particle::setVel(const glm::vec2 &vel) { Particle::vel = vel; }

const glm::vec4& Particle::getColor() const { return color; }
void Particle::setColor(const glm::vec4 &color) { Particle::color = color; }

float Particle::getLife() const { return life; }
void Particle::setLife(float life) { Particle::life = life; }
