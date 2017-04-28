#pragma once
#include <GL/glew.h>

#include "vertex3f.h"

class mesh {
public:
	mesh();

	void addVerts(vertex3f* verts);

	void draw();

	GLuint vbo;
	unsigned size;
};