#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// Open files for reading
		vertexFile.open(vertexPath, std::ios::in);
		fragmentFile.open(fragmentPath, std::ios::in);

		// Copy contents into stream
		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		// Close handles
		vertexFile.close();
		fragmentFile.close();

		// Convert stream data into strings
		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (const std::ifstream::failure& e)
	{
		printf("Error//ShaderLoad: %s\n", e.what());
	}

	// Get C strings from strings
	const GLchar* vertexSource = vertexCode.c_str();
	const GLchar * fragmentSource = fragmentCode.c_str();

	GLuint vertexShader, fragmentShader;
	GLint success;
	GLchar infoLog[512];

	// Create vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	// Check for compile errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		printf("Error//ShaderCompile: %s\n", infoLog);
	}

	// Create fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	// Check for compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		printf("Error//ShaderCompile: %s\n", infoLog);
	}

	// Create shader program
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// Check for linker errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		printf("Error//ShaderLink: %s\n", infoLog);
	}

	// Clean up shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader(const ShaderSource& s) {
	printf("%s\n%s\n", s.vertexSource, s.fragmentSource);

	GLuint vertexShader, fragmentShader;
	GLint success;
	GLchar infoLog[512];

	// Create vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &s.vertexSource, nullptr);
	glCompileShader(vertexShader);

	// Check for compile errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		printf("Error//ShaderCompile: %s\n", infoLog);
	}

	// Create fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &s.fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	// Check for compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		printf("Error//ShaderCompile: %s\n", infoLog);
	}

	// Create shader program
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	// Check for linker errors
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		printf("Error//ShaderLink: %s\n", infoLog);
	}

	// Clean up shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::uInt(const GLchar * name, GLint value) {
	glUniform1i(glGetUniformLocation(program, name), value);
}

void Shader::uFloat(const GLchar* name, GLfloat value) {
	glUniform1f(glGetUniformLocation(program, name), value);
}

void Shader::uVector3(const GLchar* name, GLfloat x, GLfloat y, GLfloat z) {
	glUniform3f(glGetUniformLocation(program, name), x, y, z);
}

void Shader::uVector3(const GLchar* name, const glm::vec3& value) {
	glUniform3f(glGetUniformLocation(program, name), value.x, value.y, value.z);
}	

void Shader::uVector4(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	glUniform4f(glGetUniformLocation(program, name), x, y, z, w);
}

void Shader::uVector4(const GLchar* name, const glm::vec4& value) {
	glUniform4f(glGetUniformLocation(program, name), value.x, value.y, value.z, value.w);
}

void Shader::uMatrix4(const GLchar* name, const glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::uPointLights(const std::vector<PointLight>& p) {
	for (int i = 0; i < p.size(); i++) {
		uVector3(std::string("pLights[" + std::to_string(i) + "].pos").c_str(), p[i].pos);
		uVector3(std::string("pLights[" + std::to_string(i) + "].ambient").c_str(), p[i].ambient);
		uVector3(std::string("pLights[" + std::to_string(i) + "].diffuse").c_str(), p[i].diffuse);
		uVector3(std::string("pLights[" + std::to_string(i) + "].specular").c_str(), p[i].specular);
	}
}

void Shader::uPointLight(PointLight p, int idx) {
	uVector3(std::string("pLights[" + std::to_string(idx) + "].pos").c_str(), p.pos);
	uVector3(std::string("pLights[" + std::to_string(idx) + "].ambient").c_str(), p.ambient);
	uVector3(std::string("pLights[" + std::to_string(idx) + "].diffuse").c_str(), p.diffuse);
	uVector3(std::string("pLights[" + std::to_string(idx) + "].specular").c_str(), p.specular);
}
