#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <string>

class Shader;

struct Glyph {
	GLuint texture;
	glm::vec2 size;
	glm::vec2 bearing;
	long offset;
};

using Charset = std::map<char, Glyph>;

class TextRenderer {
public:
	TextRenderer();
	~TextRenderer();

	void LoadFont(const char* font, FT_UInt height);

	void DrawText(std::string text, GLfloat x, GLfloat y, GLfloat scl, glm::vec3 color, std::string font);

private:
	FT_Library ftlib;

	Shader* shader;
	glm::mat4 proj;

	GLuint vao;
	GLuint vbo;

	std::map<std::string, Charset> loadedFonts;
 };