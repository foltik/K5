#pragma once
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 texCoords;
};

class Mesh {
public:
	Mesh(std::vector<Vertex> verts, std::vector<GLuint> inds, std::vector<Texture> texs);

	void Draw(Shader shader);

	std::vector<Vertex> verticies;
	std::vector<GLuint> indicies;
	std::vector<Texture> textures;

private:
	void genMesh();

	GLuint vao;
	GLuint vbo;
	GLuint ebo;
};
