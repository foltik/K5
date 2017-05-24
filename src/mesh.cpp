#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> verts, std::vector<GLuint> inds, std::vector<Texture> texs) {
	verticies = verts;
	indicies = inds;
	textures = texs;

	genMesh();
}

void Mesh::Draw(Shader* shader) {
	int diffuse = 1;
	int specular = 1;

	for (int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string name = textures[i].type;
		std::string number = std::to_string(name == "diffuse" ? diffuse++ : specular++);
		std::string var = "texture_" + name + number;

		//shader->uFloat(var.c_str(), (GLfloat)i);
		glUniform1i(glGetUniformLocation(shader->program, var.c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].texture);
	}
	glActiveTexture(GL_TEXTURE0);

	shader->uFloat("material.shine", 16.0f);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, (GLsizei)indicies.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);

	for (int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, norm));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tex));

	glBindVertexArray(0);
}