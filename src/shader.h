#pragma once
#include <fstream>
#include <sstream>

#include <GL/glew.h>

class Shader {
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void Use() { glUseProgram(program); }

	GLuint program;
};