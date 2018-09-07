#include "DrawShapes.h"

DrawShapes::DrawShapes(const GLchar *vertexShader_path, const GLchar *fragmentShader_path) {
	Shader shader(vertexShader_path, fragmentShader_path);
	shader.compile();
	// shader.printShaderFile();	// for debugging

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

// Set up vertex data (and buffer(s)) and attribute pointers
void DrawShapes::setupTriangle() {
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

	GLint posAttrib = glGetAttribLocation(Program, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	GLint colorAttrib = glGetAttribLocation(Program, "color");
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void DrawShapes::drawTriangle(){
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}


void DrawShapes::setupQuad() {
	float vertices[] = {
			// coord				// color
		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f, // Top-left
		 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f, // Top-right
		 0.5f, -0.5f, 0.0f, 	0.0f, 0.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f  // Bottom-left
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(Program, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	GLint colorAttrib = glGetAttribLocation(Program, "color");
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
}

void DrawShapes::drawQuad() {
	// draw quad with indices
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void DrawShapes::texturedQuad(string textureFilePath) {
	// vertices for quad
	float vertices[] = {
		// coord					// color		// texture coords
		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// Top-left
		 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		// Top-right
		 0.5f, -0.5f, 0.0f, 	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,		// Bottom-right
		-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f		// Bottom-left
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(Program, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(posAttrib);

	GLint colorAttrib = glGetAttribLocation(Program, "color");
	glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(colorAttrib);

	GLint textureAttrib = glGetAttribLocation(Program, "textCoord");
	glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(textureAttrib);

	// load texture
	Texture texture(textureFilePath);
	texture.loadTexture(this->Program);

	texture2d = texture.getTexture();
}

void DrawShapes::drawTexturedQuad() {
	glBindTexture(GL_TEXTURE_2D, texture2d);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

DrawShapes::~DrawShapes(){
	// De-allocate all resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}