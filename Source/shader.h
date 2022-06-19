#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

struct PointLight {
	glm::vec3 pos;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class ShaderSource {
public:
	ShaderSource(const GLchar* vertexSrc, const GLchar* fragmentSrc) {
		vertexSource = vertexSrc;
		fragmentSource = fragmentSrc;
	}

	const GLchar* vertexSource;
	const GLchar* fragmentSource;
};

class Shader {
public:
	Shader(std::string vertexPath, std::string fragmentPath);
	Shader(const ShaderSource& s);
	~Shader() = default;

	void uInt(const GLchar* name, GLint value);
	void uFloat(const GLchar* name, GLfloat value);
	void uVector2(const GLchar* name, GLfloat x, GLfloat y);
    void uVector2(const GLchar* name, const glm::vec2& value);
	void uVector3(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);
	void uVector3(const GLchar* name, const glm::vec3& value);
	void uVector4(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	void uVector4(const GLchar* name, const glm::vec4& value);
	void uMatrix4(const GLchar* name, const glm::mat4& value);
	void uPointLight(PointLight p, int idx);
	void uPointLights(const std::vector<PointLight>& p);

	void Use() { glUseProgram(program); }

private:
	GLuint program;

    void compileShader(const GLchar* vertexSource, const GLchar* fragmentSource);
};