#include "Cube.h"

Cube::Cube(string textureFilePath)
{
	// vertices for quad
	float vertices[] = {
		// coord					// color		// texture coords
		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// Top-left
		 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		// Top-right
		 0.5f, -0.5f, 0.0f, 	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,		// Bottom-right
		-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f		// Bottom-left
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(Program, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(posAttrib);

	GLint textureAttrib = glGetAttribLocation(Program, "textCoord");
	glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(textureAttrib);

	// load texture
	Texture texture(textureFilePath);
	texture.loadTexture(this->Program);

	texture2d = texture.getTexture();
}

void Cube::drawCube() {
	glBindTexture(GL_TEXTURE_2D, texture2d);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

Cube::~Cube()
{
}
