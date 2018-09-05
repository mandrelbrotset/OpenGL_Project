#include "Shader.h"

// Constructor generates the shader on the fly
Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath){
	// Retrieve the vertex/fragment source code from filePath
	ifstream vShaderFile;
	ifstream fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(ifstream::badbit);
	fShaderFile.exceptions(ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure e)
	{
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	vShaderCode = vertexCode.c_str();
	fShaderCode = fragmentCode.c_str();
}

void Shader::compile() {
	// Compile shaders
	GLint success;
	GLchar infoLog[512];
	
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}
}

void Shader::printShaderFile() {
	cout << "Vertex Shader code" << endl;
	cout << vertexCode << endl;
	cout << "Fragment Shader code" << endl;
	cout << fragmentCode << endl;
}

vertexFragmentShader Shader::getCompiledShaders() {
	vertexFragmentShader temp;
	temp.vertex = vertex;
	temp.fragment = fragment;

	return temp;
}
