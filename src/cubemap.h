#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader;

class Cubemap {
public:
    Cubemap() = default;
    explicit Cubemap(const char* textures[6]);
    ~Cubemap();

    void Draw(glm::mat4 proj, glm::mat4 view);

private:
    GLuint vao;
    GLuint vbo;
    GLuint tex;
    Shader* shader = nullptr;
};
