#pragma once

#include <iostream>
#include "GL/glew.h"
#include "stb_image.h"

using namespace std;

class Texture
{
private:
	string texturePath;
	GLuint texture;
	int width, height, nrChannels;
	unsigned char* image;

public:
	Texture(string);
	void loadTexture(GLuint);
	GLuint getTexture();
	~Texture();
};

