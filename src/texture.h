#pragma once
#include <GL/glew.h>

struct Texture {
	void Use() { glBindTexture(GL_TEXTURE_2D, textureId); }

	int width;
    int height;
	GLuint textureId;
};

