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
private:
	GLuint vertex, fragment;
	const GLchar *vShaderCode;
	const GLchar *fShaderCode;
	string vertexCode;
	string fragmentCode;
	GLint success;
	GLchar infoLog[512];
public:
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
	GLuint Program;
	void printShaderFile();
	void compile();
	void linkProgram();
	void use();
};

#endif // !Shader_h