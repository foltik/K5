#pragma once
#include <string>
#include <GL/glew.h>

enum class TextureType {
    SPRITE,
    DIFFUSE,
    SPECULAR,
    UNKNOWN
};

struct Texture {
	void Use() { glBindTexture(GL_TEXTURE_2D, textureId); }

    TextureType type;
    std::string path;
	int width;
    int height;
	GLuint textureId;
};

namespace {
    std::string nameFromTextureType(TextureType type) {
        if (type == TextureType::SPRITE)
            return "sprite";
        else if (type == TextureType::DIFFUSE)
            return "diffuse";
        else if (type == TextureType::SPECULAR)
            return "specular";
        else
            return "unknown";
    }
}

