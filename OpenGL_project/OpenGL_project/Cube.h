#pragma once

#include "Shader.h"
#include <GL\glew.h>
#include "Texture.h"

class Cube{
private:
	GLuint VBO, VAO, EBO;
	GLuint texture2d;
public:
	Cube(Shader shader, string textureFilePath);
	void drawCube();
	~Cube();
};

