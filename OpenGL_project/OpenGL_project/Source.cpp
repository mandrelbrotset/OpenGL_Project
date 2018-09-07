#include <iostream>
#include <chrono>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Shader.h"
#include "DrawShapes.h"

using namespace std;

// The MAIN function, from here we start the application and run the game loop
int main()
{

	// create a window with width 800, height 600 and name "Learn OpenGL"
	Window window(800, 600, "Learn OpenGL");

	//const char *vertexShader = "res/shaders/triangle.vshader";
	//const char *fragmentShader = "res/shaders/triangle.fshader";

	const char *vertexShader = "res/shaders/textured.vshader";
	const char *fragmentShader = "res/shaders/textured.fshader";

	//---------------------------------------
	DrawShapes shape(vertexShader, fragmentShader);
	shape.linkProgram();
	//shape.setupTriangle();
	//shape.setupQuad();
	//shape.texturedQuad("res/images/brickWall.jpg");
	shape.texturedQuad("res/images/ubuntu.png");
	//---------------------------------------

	// Game loop
	while (window.isNotClosed())
	{

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.6f, 0.2f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//-----------------------------------------------------
		shape.use();
		//shape.drawTriangle();
		//shape.drawQuad();
		shape.drawTexturedQuad();

		//-----------------------------------------------------

		// Swap the screen buffers
		window.swapBuffers();
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return EXIT_SUCCESS;
}

