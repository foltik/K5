#pragma once
#include "engine.h"

#include <iostream>

#include <GL/glew.h>
#include <SOIL/SOIL.h>

class Texture {
public:
	Texture() = default;
	Texture(const char* path);
	Texture(const char* path, const char* dir);

	void Use();

	GLint width, height;
	GLuint texture;
	std::string m_path;
	std::string type;

private:
	void genTexture(const char* path);
};
