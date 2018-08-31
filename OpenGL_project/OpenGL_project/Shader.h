#ifndef Shader_h
#define Shader_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

using namespace std;

class Shader
{
protected:
	const GLchar *vShaderCode;
	const GLchar *fShaderCode;
	GLint success;
	GLchar infoLog[512];
	const char * vertexShaderPath;
	const char * fragmentShaderPath;
public:
	GLuint Program;
	Shader();
	void initialize();
	void virtual linkProgram() = 0;
	// void use();
};

#endif // !Shader_h