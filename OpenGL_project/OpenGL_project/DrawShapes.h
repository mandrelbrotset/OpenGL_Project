#ifndef DrawShapes_h
#define DrawShapes_h

#include "Shader.h"
#include <GL\glew.h>

class DrawShapes: public Shader
{
public:
	GLuint VBO, VAO;
	void setupTriangle(const char *, const char *);
	void draw();
	void linkProgram();
	DrawShapes();
	~DrawShapes();
};

#endif // !DrawShapes_h