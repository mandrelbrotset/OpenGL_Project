#ifndef DrawShapes_h
#define DrawShapes_h

#include "Shader.h"
#include <GL\glew.h>
#include "CompiledShaders.h"
#include <SOIL2\SOIL2.h>

class DrawShapes{
private:
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	GLuint VBO, VAO, EBO;
	GLuint texture;

public:
	GLuint Program;
	DrawShapes(const GLchar *, const GLchar *);
	void linkProgram();
	void use();
	void setupTriangle();
	void drawTriangle();
	void setupTexturedRect(string texturePath);
	void drawTexturedRect();
	~DrawShapes();
};

#endif // !DrawShapes_h