#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Texture;
class Shader;

class SpriteRenderer {
public:
    explicit SpriteRenderer(glm::mat4 projection);
    ~SpriteRenderer();

    void DrawSprite(Texture* tex, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 color);

private:
    Shader* shader;
    GLuint vao;
    glm::mat4 proj;
};