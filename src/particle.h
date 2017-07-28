#pragma once

#include <glm/glm.hpp>

class Particle {
public:
    const glm::vec2& getPos() const;
    void setPos(const glm::vec2 &pos);

    const glm::vec2& getVel() const;
    void setVel(const glm::vec2 &vel);

    const glm::vec4& getColor() const;
    void setColor(const glm::vec4 &color);

    float getLife() const;
    void setLife(float life);

    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec4 color;
    float life;
};
