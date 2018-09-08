#ifndef DrawShapes_h
#define DrawShapes_h

#include "Shader.h"
#include <GL\glew.h>
#include "Texture.h"

class DrawShapes{
private:
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	GLuint VBO, VAO, EBO;
	GLuint texture2d;

public:
	//DrawShapes();
	void setupTriangle(Shader shader);
	void drawTriangle();
	void setupQuad(Shader shader);
	void drawQuad();
	void texturedQuad(Shader shader, string texturePath);
	void drawTexturedQuad();
	~DrawShapes();
};

#endif // !DrawShapes_h