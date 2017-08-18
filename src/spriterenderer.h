#pragma once
#include "texture.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SpriteRenderer {
public:
    SpriteRenderer(glm::mat4 projection);
    ~SpriteRenderer();

    void DrawSprite(Texture& tex, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 color);

private:
    Shader* shader;
    GLuint vao;
    glm::mat4 proj;
};