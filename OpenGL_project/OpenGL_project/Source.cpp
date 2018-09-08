#include <iostream>

#include <GL/glew.h>		// GLEW
#include <GLFW/glfw3.h>		// GLFW

#include "Window.h"
#include "Shader.h"
#include "DrawShapes.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	//shape.texturedQuad("res/images/ubuntu.png");
	//---------------------------------------

	// Game loop
	while (window.isNotClosed())
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.6f, 0.2f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//-----------------------------------------------------
		shape.use();
		//shape.drawTriangle();
		//shape.drawQuad();
		shape.drawTexturedQuad();

		//-----------------------------------------------------
		// Create transformations
		glm::mat4 transform;
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (GLfloat)glfwGetTime() * -5.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		// Get matrix's uniform location and set matrix
		GLint transformLocation = glGetUniformLocation(shape.Program, "transform");
		glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));


		//-----------------------------------------------------

		// Swap the screen buffers
		window.swapBuffers();
		// reset key state to false
		window.resetKeys();
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return EXIT_SUCCESS;
}

