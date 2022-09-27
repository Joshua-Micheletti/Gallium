#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION  
#include <stb_image.h>

void Texture::loadTexture(std::string filepath) {
    glGenTextures(1, &this->id_);
	glBindTexture(GL_TEXTURE_2D, this->id_);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("COULD NOT LOAD TEXTURE\n");
	}
	stbi_image_free(data);
}

unsigned int Texture::id() {
    return(this->id_);
}

void Texture::printFull() {
    printf("ID: %d\n", this->id_);
}