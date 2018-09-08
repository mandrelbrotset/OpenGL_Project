#include <iostream>

#include <GL/glew.h>		// GLEW
#include <GLFW/glfw3.h>		// GLFW

#include "Window.h"
#include "Shader.h"
#include "DrawShapes.h"
#include "Cube.h"

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

	//const char *vertexShader = "res/shaders/textured.vshader";
	//const char *fragmentShader = "res/shaders/textured.fshader";

	const char *vertexShader = "res/shaders/cube.vshader";
	const char *fragmentShader = "res/shaders/cube.fshader";

	Shader shader(vertexShader, fragmentShader);
	shader.compile();
	shader.linkProgram();

	//---------------------------------------
	string ubuntuLogo = "res/images/ubuntu.png";
	string brick = "res/images/brickWall.jpg";

	Cube cube(shader, brick);
	//Cube cube(shader, ubuntuLogo);
	// DrawShapes shape;
	// shape.texturedQuad(shader, brick);
	// shape.texturedQuad(shader, ubuntuLogo);
	//---------------------------------------

	// maths stuff for projections
	glm::mat4 projection;
	projection = glm::perspective(45.0f, (GLfloat)window.getWindowWidth() / (GLfloat)window.getWindowHeight(), 0.1f, 100.0f);

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
		shader.use();

		//---------- projection ----------------
		// Create transformations
		glm::mat4 model;
		glm::mat4 view;
		// use with perspective projection
		model = glm::rotate(model, (GLfloat)glfwGetTime() * 1.0f, glm::vec3(0.5f, 1.0f, 0.0f)); 
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		// Get their uniform location
		GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");
		GLint projLoc = glGetUniformLocation(shader.Program, "projection");

		// Pass them to the shaders
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// ----------------------------------------------
		// draw a quad with texture
		// shape.drawTexturedQuad();
		cube.drawCube();

		//-----------------------------------------------------
		// Create transformations
		glm::mat4 transform;
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (GLfloat)glfwGetTime() * -5.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		// Get matrix's uniform location and set matrix
		// GLint transformLocation = glGetUniformLocation(shape.Program, "transform");
		GLint transformLocation = glGetUniformLocation(shader.Program, "transform");
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

