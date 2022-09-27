#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION  
#include <stb_image.h>

void Texture::loadTexture(std::string filepath) {
	this->type_ = GL_TEXTURE_2D;

    glGenTextures(1, &this->id_);
	glBindTexture(GL_TEXTURE_2D, this->id_);

	stbi_set_flip_vertically_on_load(true); 

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

void Texture::loadCubemap(std::vector<std::string> faces) {
	this->type_ = GL_TEXTURE_CUBE_MAP;

	glGenTextures(1, &this->id_);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->id_);

	stbi_set_flip_vertically_on_load(false); 

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++) {
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			GLenum format;
			switch (nrChannels)
			{
			case 1:
				format = GL_LUMINANCE;
				break;
			case 2:
				format = GL_LUMINANCE_ALPHA;
				break;
			case 3:
				format = GL_RGB;
				break;
			case 4:
				format = GL_RGBA;
				break;
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


GLenum Texture::type() {
	return(this->type_);
}

unsigned int Texture::id() {
    return(this->id_);
}

void Texture::printFull() {
    printf("ID: %d\n", this->id_);
}