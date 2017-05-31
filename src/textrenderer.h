#pragma once
#include "engine.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <map>
#include <string>

struct Glyph {
	GLuint texture;
	glm::vec2 size;
	glm::vec2 bearing;
	GLfloat offset;
};

using Charset = std::map<char, Glyph>;

class TextRenderer {
public:
	TextRenderer();
	~TextRenderer();

	void LoadFont(const char* font, FT_UInt height);

	void DrawText(std::string text, GLfloat x, GLfloat y, GLfloat scl, glm::vec3 color, const char* font);

private:
	FT_Library ftlib;

	Shader* shader;
	glm::mat4 proj;

	GLuint vao;
	GLuint vbo;

	std::map<const char*, Charset> loadedFonts;
 };