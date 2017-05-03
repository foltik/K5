#pragma once
#include <iostream>

#include <GL/glew.h>
#include <SOIL/SOIL.h>

class Texture {
public:
	Texture(const char* path);

	void Use();

	GLint width, height;
	GLuint texture;
};
