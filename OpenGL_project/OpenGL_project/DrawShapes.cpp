#include "DrawShapes.h"

DrawShapes::DrawShapes(const GLchar *vertexShader_path, const GLchar *fragmentShader_path) {
	Shader shader(vertexShader_path, fragmentShader_path);
	
	vertexFragmentShader compiledShaders;

	compiledShaders = shader.getCompiledShaders();

	vertex = compiledShaders.vertex;
	fragment = compiledShaders.fragment;
}

void DrawShapes::linkProgram() {
	GLint success;
	GLchar infoLog[512];

	// Shader Program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	// Print linking errors if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void DrawShapes::use() {
	glUseProgram(this->Program);
}

void DrawShapes::setupTriangle() {
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// position				// color
		-0.5f, -0.5f, 0.0f,		0.5f, 0.5f, 0.5f,	// Left
		0.5f, -0.5f, 0.0f,		0.5f, 0.5f, 0.5f,	// Right
		0.0f,  0.5f, 0.0f,		0.5f, 0.5f, 0.5f	// Top
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void DrawShapes::drawTriangle(){
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

DrawShapes::~DrawShapes(){
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}