#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>
#include <vector>
#include <algorithm>

struct GlyphData {
	glm::vec2 size;
	glm::vec2 bearing;
	glm::vec2 advance;
	float offset;
};

struct Glyph {
	glm::vec2 size;
	glm::vec2 bearing;
	glm::vec2 advance;
	glm::vec2 bl;
	glm::vec2 tl;
	glm::vec2 tr;
	glm::vec2 br;
};

class Atlas {
public:
	Atlas() = default;
	Atlas(std::string font, FT_UInt height);

	Glyph getGlyph(char c);

	GLuint Texture() const { return texture; }
	float Width() const { return width; }
	float Height() const { return height; }

private:
	GLuint texture;

	float width;
	float height;

	std::vector<GlyphData> glyphs = std::vector<GlyphData>(255);
};