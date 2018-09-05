#ifndef Shader_h
#define Shader_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "CompiledShaders.h"
#include <GL/glew.h>

using namespace std;

class Shader
{
private:
	GLuint vertex, fragment;
	const GLchar *vShaderCode;
	const GLchar *fShaderCode;
	string vertexCode;
	string fragmentCode;
public:
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
	void printShaderFile();
	void compile();
	// GLint getUniformLocation(GLuint programID, const char *);
	vertexFragmentShader getCompiledShaders();
};

#endif // !Shader_h