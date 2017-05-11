#pragma once
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void uFloat(const GLchar* name, GLfloat value);
	void uVector3(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);
	void uVector3(const GLchar* name, const glm::vec3& value);
	void uVector4(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void uVector4(const GLchar* name, const glm::vec4& value);
	void uMatrix4(const GLchar* name, const glm::mat4& value);
	
	void Use() { glUseProgram(program); }

	GLuint program;
};
