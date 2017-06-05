#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <vector>
#include <map>
#include <string>

#include "engine.h"
#include "shader.h"
#include "atlas.h"

class TextRenderer {
public:
	void LoadFont(std::string font, FT_UInt height);

	void DrawText(std::string text, GLfloat x, GLfloat y);

	float Scale() const { return currentScale; }
	void Scale(float val) { currentScale = val; }

	glm::vec3 Color() const { return currentColor; }
	void Color(const glm::vec3& val) { currentColor = val; }

	std::string Font() const { return currentFont; }
	void Font(std::string val) { currentFont = val; }

	static TextRenderer& Instance() {
		static TextRenderer instance;
		return instance;
	}

protected:
	TextRenderer();
	TextRenderer(const TextRenderer&) = delete;
	TextRenderer(TextRenderer&&) = delete;
	void operator=(const TextRenderer&) = delete;
	void operator=(TextRenderer&&) = delete;

private:
	std::map<std::string, Atlas> loadedFonts;

	float currentScale = 1.0f;
	glm::vec3 currentColor = glm::vec3(1.0f, 1.0f, 1.0f);
	std::string currentFont;

	glm::mat4 proj;

	ShaderSource shaderSource = ShaderSource(
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
	);

	Shader shader = Shader(shaderSource);
 };