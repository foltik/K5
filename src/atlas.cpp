#include "atlas.h"

//Load up to ascii 255, excluding the first 31 non - glyphs

Atlas::Atlas(std::string font, FT_UInt height) {
	// Initialize FreeType
	FT_Library ftlib;
	if (FT_Init_FreeType(&ftlib))
		throw std::runtime_error("Error//Lib: FreeType Initialization Failed\n");

	// Load the typeface
	std::string path = "fonts/" + font + ".ttf";
	FT_Face face;
	if (FT_New_Face(ftlib, path.c_str(), 0, &face))
		throw std::runtime_error("Error//FontLoad: Failed to load font " + std::string(path) + "\n");

	// Set the proper height
	FT_Set_Pixel_Sizes(face, 0, height);

	// Calculate the dimensions of the atlas
	int aWidth = 0;
	int aHeight = 0;
	for (GLubyte i = 32; i < 255; i++) {
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			printf("Error//GlyphLoad: Failed to load glyph %d\n", i);
			continue;
		}

		// Update the glyph data
		glyphs.insert(glyphs.begin() + i, {
			glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			glm::vec2(face->glyph->advance.x, face->glyph->advance.y),
			(float)aWidth
		});

		aHeight = std::max(aHeight, face->glyph->bitmap.rows);
		aWidth += face->glyph->bitmap.width;
	}
	width = (float)aWidth;
	height = (float)aHeight;

	// Set up the texture with blank data to be filled
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RED,
		width, height,
		0, GL_RED, GL_UNSIGNED_BYTE,
		nullptr
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Actually load the texture with data
	int offset = 0;
	for (GLubyte i = 32; i < 255; i++) {
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			printf("Error//GlyphLoad: Failed to load glyph %d\n", i);
			continue;
		}

		glTexSubImage2D(
			GL_TEXTURE_2D, 0, 
			offset, 0, 
			face->glyph->bitmap.width, face->glyph->bitmap.rows, 
			GL_ALPHA, GL_UNSIGNED_BYTE, 
			face->glyph->bitmap.buffer
		);

		offset += face->glyph->bitmap.width;
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ftlib);
}

Glyph Atlas::getGlyph(char c) {
	if (c > 255)
		throw std::runtime_error("Error//GetGlyph: Character out of range");

	GlyphData d = glyphs[c];

	height = 48.0f;

	return {
		d.size,
		d.bearing,
		d.advance,
		glm::vec2(d.offset / width, 0.0f),
		glm::vec2(d.offset / width, d.size.y / height),
		glm::vec2((d.offset + d.size.x) / width, d.size.y / height),
		glm::vec2((d.offset + d.size.x) / width, 0.0f)
	};
}
