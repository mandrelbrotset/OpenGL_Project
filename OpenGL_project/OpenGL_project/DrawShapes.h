#ifndef DrawShapes_h
#define DrawShapes_h

#include "Shader.h"
#include <GL\glew.h>
#include "CompiledShaders.h"
#include "Texture.h"

class DrawShapes{
private:
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	GLuint VBO, VAO, EBO;
	GLuint texture2d;

public:
	GLuint Program;
	DrawShapes(const GLchar *, const GLchar *);
	void linkProgram();
	void use();
	void setupTriangle();
	void drawTriangle();
	void setupQuad();
	void drawQuad();
	void texturedQuad(string texturePath);
	void drawTexturedQuad();
	~DrawShapes();
};

#endif // !DrawShapes_h