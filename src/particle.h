#pragma once

#include <glm/glm.hpp>

class Particle {
public:
    Particle() = default;
    Particle(glm::vec2 position, glm::vec2 velocity, glm::vec4 col, float life, float decay);
    Particle(glm::vec2 position, glm::vec2 velocity, glm::vec4 col, glm::vec4 colDecay, float life, float decay);

    void update();

    const glm::vec2& getPos() const;
    void setPos(const glm::vec2 &pos);

    const glm::vec2& getVel() const;
    void setVel(const glm::vec2 &vel);

    const glm::vec4& getColor() const;
    void setColor(const glm::vec4 &color);

    const glm::vec4& getColorDecay() const;
    void setColorDecay(const glm::vec4& colorDecay);

    float getLife() const;
    void setLife(float life);

    float getLifeDecay() const;
    void setLifeDecay(float lifeDecay);

private:
    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec4 color;
    glm::vec4 colorDecay;

    float life;
    float lifeDecay;
};
