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
public:
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
	vertexFragmentShader getCompiledShaders();
	// void use();
};

#endif // !Shader_h