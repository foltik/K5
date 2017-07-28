#include "textrenderer.h"

TextRenderer::TextRenderer() {
	if (FT_Init_FreeType(&ftlib))
		throw new std::runtime_error("Error//Lib: FreeType Initialization Failed\n");

	shader = new Shader(ShaderSource(
		R"(
			#version 330 core
			layout (location = 0) in vec4 vertex;
			out vec2 TexCoord;

			uniform mat4 proj;

			void main() {
				gl_Position = proj * vec4(vertex.xy, 0.0, 1.0);
				TexCoord = vertex.zw;
			}
		)",

		R"(
			#version 330 core
			in vec2 TexCoord;
			out vec4 color;

			uniform sampler2D text;
			uniform vec3 textColor;

			void main() {
				vec4 sample = vec4(1.0, 1.0, 1.0, texture(text, TexCoord).r);
				color = vec4(textColor, 1.0) * sample;
			}
		)"
	));

	proj = glm::ortho(0.0f, (GLfloat)CEngine::wndW, 0.0f, (GLfloat)CEngine::wndH);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

TextRenderer::~TextRenderer() {
	FT_Done_FreeType(ftlib);

	delete shader;
}

void TextRenderer::LoadFont(const char* path, FT_UInt height) {
	std::string p = CEngine::Instance().path + std::string(path);
    std::string name = p.substr(p.find_last_of("/") + 1);

	path = p.c_str();

	FT_Face face;
	
	if (FT_New_Face(ftlib, path, 0, &face))
		throw new std::runtime_error("Error//FontLoad: Failed to load font " + std::string(path) + "\n");

	FT_Set_Pixel_Sizes(face, 0, height);

	Charset c;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 255 ascii characters
	for (GLubyte i = 0; i < 255; i++) {
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			printf("Error//GlyphLoad: Failed to load glyph %d\n", i);
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);		

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		c.insert({(char)i, {
            texture,
            glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        }});
	}

	loadedFonts.insert(std::make_pair(name, c));

	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
}

void TextRenderer::DrawText(std::string text, GLfloat x, GLfloat y, GLfloat scl, glm::vec3 color, std::string font) {
	shader->Use();

	shader->uVector3("textColor", color);
	shader->uMatrix4("proj", proj);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	for (auto c : text) {
        if (!loadedFonts.count(font)) {
            printf("Error//TextDraw: Font %s not found\n", font);
            return;
        }

		Glyph g = loadedFonts[font][c];

		GLfloat px = x + g.bearing.x * scl;
		GLfloat py = y - (g.size.y - g.bearing.y) * scl;
		GLfloat w = g.size.x * scl;
		GLfloat h = g.size.y * scl;

		GLfloat verts[6][4] = {
			{ px, py + h,     0.0, 0.0 },
			{ px, py,         0.0, 1.0 },
			{ px + w, py,     1.0, 1.0 },
			{ px, py + h,     0.0, 0.0 },
			{ px + w, py,     1.0, 1.0 },
			{ px + w, py + h, 1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, g.texture);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (g.offset / 64) * scl;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}