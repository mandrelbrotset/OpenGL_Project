#include "Texture.h"

Texture::Texture(GLchar* filePath):
	texturePath(filePath)
{
	// image = SOIL_load_image("sample.png", &width, &height, 0, SOIL_LOAD_RGB);
}

void Texture::loadTexture(GLuint programId) {
	/* load an image file directly as a new OpenGL texture */
	/*
	glGenTextures(1, texture);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(programId, "texKitten"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/
}

GLuint Texture::getTexture() {
	return *texture;
}

Texture::~Texture()
{
}
