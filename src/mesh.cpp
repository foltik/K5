#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> verts, std::vector<GLuint> inds, std::vector<Texture> texs) {
	verticies = verts;
	indicies = inds;
	textures = texs;

	genMesh();
}

void Mesh::Draw(Shader shader) {
	// TODO: TEXTURES
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
}

void Mesh::genMesh() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(GLuint), &verticies[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), &indicies[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)&reinterpret_cast<char const volatile&>(((Vertex*)0)->norm));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)&reinterpret_cast<char const volatile&>(((Vertex*)0)->texCoords));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}