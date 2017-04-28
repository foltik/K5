#include "mesh.h"

mesh::mesh() {
	glGenBuffers(size, &vbo);
}

void mesh::addVerts(vertex3f* verts) {
	size = (sizeof(verts) / sizeof(vertex3f));
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
}

void mesh::draw() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, vertex3f::size * sizeof(vec3f), 0);
	glDrawArrays(GL_TRIANGLES, 0, size);
	glEnableVertexAttribArray(0);
}