#include "resourcemanager.h"

ResourceManager::~ResourceManager() {
    for (Texture* texture : loadedTextures) {
        delete texture;
    }
}

// Looks for a texture to load, starting in "CWD/textures/"
Texture* ResourceManager::loadTexture(const std::string file) {
    if (loadedTextures.find(file) != loadedTextures.end()) {
        // If it was already loaded, just return it
        return loadedTextures[file];
    } else {
        // Otherwise figure out the whole path and load in the texture
        std::string path = CEngine::Instance().getCwd() + std::string("textures/");
        Texture* tex = genTexture(path);
        loadedTextures[file] = tex;
        return tex;
    }
}

Texture* ResourceManager::genTexture(const std::string& path) {
    auto* texture = new Texture();

	// Generate the texture object for OpenGL
	glGenTextures(1, &texture->textureId);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture->textureId);

	// Load the texture

	unsigned char* data = SOIL_load_image(path, &texture->width, &texture->height, nullptr, SOIL_LOAD_RGBA);
	if (data == nullptr) {
		printf("Error//TextureLoad: Texture %s failed to load\n", path.c_str());
		return;
	}

	// Load the texture data into the texture object and generate mipmaps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Free the texture data and unbind the texture object
	SOIL_free_image_data(data);
	glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

