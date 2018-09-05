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


void DrawShapes::setupTexturedRect(string texturePath) {
	GLfloat vertices[] =
	{
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
	};
	GLuint indices[] =
	{  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
						  
	// Load and create a texture
	int width, height;

	// ===================
	// Texture
	// ===================
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	unsigned char *image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void DrawShapes::drawTexturedRect() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(Program, "textureCoord"), 0);

	// Draw container
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

DrawShapes::~DrawShapes(){
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}