#include "shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

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
	catch (std::ifstream::failure e)
	{
		printf("Error: Shader files could not be successfully read\n");
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
		printf("Error: Shader Compilation Failed\n%s", infoLog);
		printf("---CODE---\n%s\n", vertexSource);
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
		printf("Error: Shader Compilation Failed\n%s", infoLog);
		printf("---CODE---\n%s\n", fragmentSource);
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
		printf("Error: Shader Program Linking Failed\n%s", infoLog);
	}

	// Clean up shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::uFloat(const GLchar* name, GLfloat value) {
	glUniform1f(glGetUniformLocation(this->program, name), value);
}

void Shader::uVector3(const GLchar* name, GLfloat x, GLfloat y, GLfloat z) {
	glUniform3f(glGetUniformLocation(this->program, name), x, y, z);
}

void Shader::uVector3(const GLchar* name, const glm::vec3& value) {
	glUniform3f(glGetUniformLocation(this->program, name), value.x, value.y, value.z);
}	

void Shader::uVector4(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	glUniform4f(glGetUniformLocation(this->program, name), x, y, z, w);
}

void Shader::uVector4(const GLchar* name, const glm::vec4& value) {
	glUniform4f(glGetUniformLocation(this->program, name), value.x, value.y, value.z, value.w);
}

void Shader::uMatrix4(const GLchar* name, const glm::mat4& value) {
	glUniformMatrix4fv(glGetUniformLocation(this->program, name), 1, GL_FALSE, glm::value_ptr(value));
}
