#pragma once

#include <iostream>
#include "GL/glew.h"
#include "soil/SOIL.h"

using namespace std;

class Texture
{
private:
	GLchar *texturePath;
	GLuint *texture;
	int width, height;
	unsigned char* image;

public:
	Texture(GLchar*);
	void loadTexture(GLuint);
	GLuint getTexture();
	~Texture();
};

