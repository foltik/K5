#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> verts, std::vector<GLuint> inds, std::vector<Texture> texs) {
	verticies = verts;
	indicies = inds;
	textures = texs;

	genMesh();
}

void Mesh::Draw(const Shader* shader) {
	// TODO: TEXTURES
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, (GLsizei)indicies.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
}

void Mesh::genMesh() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, (GLsizei)verticies.size() * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei)indicies.size() * sizeof(GLuint), &indicies[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, norm));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tex));

	glBindVertexArray(0);
}
