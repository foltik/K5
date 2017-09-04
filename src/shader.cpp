#include "shader.h"

#include "engine.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    vertexPath = CEngine::Instance().getCwd() + vertexPath;
    fragmentPath = CEngine::Instance().getCwd() + fragmentPath;

	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vertexFile(vertexPath, std::ios::in | std::ios::binary);
	std::ifstream fragmentFile(fragmentPath, std::ios::in | std::ios::binary);

    if (vertexFile && fragmentFile) {
        vertexFile.seekg(0, std::ios::end);
        vertexCode.resize((unsigned long)vertexFile.tellg());
        vertexFile.seekg(0, std::ios::beg);
        vertexFile.read(&vertexCode[0], vertexCode.size());
        vertexFile.close();

        fragmentFile.seekg(0, std::ios::end);
        fragmentCode.resize((unsigned long)fragmentFile.tellg());
        fragmentFile.seekg(0, std::ios::beg);
        fragmentFile.read(&fragmentCode[0], fragmentCode.size());
        fragmentFile.close();
    } else {
        printf("Error//ShaderLoad: Failed to open file %s\n", !vertexFile ? vertexPath : !fragmentFile ? fragmentPath : "null");
        return;
    }

    compileShader(vertexCode.c_str(), fragmentCode.c_str());
}

Shader::Shader(const ShaderSource& s) {
    compileShader(s.vertexSource, s.fragmentSource);
}

void Shader::compileShader(const GLchar *vertexSource, const GLchar *fragmentSource) {
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

void Shader::uInt(const GLchar * name, GLint value) {
	glUniform1i(glGetUniformLocation(program, name), value);
}

void Shader::uFloat(const GLchar* name, GLfloat value) {
	glUniform1f(glGetUniformLocation(program, name), value);
}

void Shader::uVector2(const GLchar *name, GLfloat x, GLfloat y) {
    glUniform2f(glGetUniformLocation(program, name), x, y);
}

void Shader::uVector2(const GLchar *name, const glm::vec2 &value) {
    glUniform2f(glGetUniformLocation(program, name), value.x, value.y);
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
