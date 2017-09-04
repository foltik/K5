#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Texture;

struct Vertex {
    glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 tex;
};

class Shader;

struct Model {
    void Draw(Shader *shader);

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    size_t numInds;
    std::vector<Texture*> texs;
};
