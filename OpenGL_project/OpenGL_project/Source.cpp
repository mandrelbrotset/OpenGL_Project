#include <iostream>

// GLEW
// #define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>

#include "Window.h"
#include "Shader.h"
#include "DrawShapes.h"

// The MAIN function, from here we start the application and run the game loop
int main()
{
	Window window(800, 600, "Learn OpenGL");

	const char *vertexShader = "resources/shaders/triangle.vs";
	const char *fragmentShader = "resources/shaders/triangle.frs";

	//-------------
	DrawShapes shape(vertexShader, fragmentShader);
	shape.linkProgram();
	shape.setupTriangle();
	
	//shape.setupTexturedRect();

	//-------------

	// Game loop
	while (window.isNotClosed())
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//-------------
		shape.use();
		shape.drawTriangle();

		// Swap the screen buffers
		window.swapBuffers();
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return EXIT_SUCCESS;
}

