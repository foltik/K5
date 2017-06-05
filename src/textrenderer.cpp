#include "textrenderer.h"

TextRenderer::TextRenderer() {
	proj = glm::ortho(0.0f, (GLfloat)CEngine::wndW, 0.0f, (GLfloat)CEngine::wndH);
}

void TextRenderer::LoadFont(std::string font, FT_UInt height) {
	loadedFonts.insert(std::make_pair(font, Atlas(font, height)));
}

void TextRenderer::DrawText(std::string text, GLfloat x, GLfloat y) {
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	shader.Use();

	shader.uVector3("textColor", currentColor);
	shader.uMatrix4("proj", proj);

	for (char c : text) {
		Glyph g = loadedFonts[currentFont].getGlyph(c);

		GLfloat px = x + g.bearing.x * currentScale;
		GLfloat py = y - (g.size.y - g.bearing.y) * currentScale;
		GLfloat w = g.size.x * currentScale;
		GLfloat h = g.size.y * currentScale;

		GLfloat verts[6][4] = {
			{ px, py, g.bl.x, g.bl.y },
			{ px, py + h, g.tl.x, g.tl.y },
			{ px + w, py + h, g.tr.x, g.tr.y },
			{ px, py, g.bl.x, g.bl.y },
			{ px + w, py + h, g.tr.x, g.tr.y },
			{ px + w, py, g.br.x, g.br.y }
		};

		glActiveTexture(GL_TEXTURE0);

		glBindVertexArray(vao);
		
		glBindTexture(GL_TEXTURE_2D, loadedFonts[currentFont].Texture());

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (g.advance.x / 64) * currentScale;
	}
}