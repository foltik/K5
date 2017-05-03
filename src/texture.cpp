#include "texture.h"

Texture::Texture(const char* path) {
	// Generate the texture object for OpenGL
	glGenTextures(1, &texture);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, this->texture);

	// Load the texture
	unsigned char* data = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	if (data == nullptr) {
		printf("Error//TextureLoad: Texture %s failed to load\n", path);
		return;
	}

	// Load the texture data into the texture object and generate mipmaps	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free the texture data and unbind the texture object
	SOIL_free_image_data(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Use() {
	glBindTexture(GL_TEXTURE_2D, this->texture);
}
