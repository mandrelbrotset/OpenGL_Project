#include <iostream>

#include <GL/glew.h>		// GLEW
#include <GLFW/glfw3.h>		// GLFW

#include "Window.h"
#include "Shader.h"
#include "DrawShapes.h"
#include "Cube.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


// The MAIN function, from here we start the application and run the game loop
int main()
{
	// create a window with width 800, height 600 and name "Learn OpenGL"
	Window window(WIDTH, HEIGHT, "Learn OpenGL");
	glfwSetKeyCallback(window.getWindow(), KeyCallback);
	glfwSetCursorPosCallback(window.getWindow(), MouseCallback);

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

	glm::vec3 cubePositions[] =
	{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f, 3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f, 2.0f, -2.5f),
		glm::vec3(1.5f, 0.2f, -1.5f),
		glm::vec3(-1.3f, 1.0f, -1.5f)
	};

	// Game loop
	while (window.isNotClosed())
	{
		camera.updateFrameTime();

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		// react to keyboard input
		DoMovement();

		// Render
		// Clear the colorbuffer
		glClearColor(0.6f, 0.2f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//-----------------------------------------------------
		shader.use();

		//---------- projection ----------------
		glm::mat4 projection;
		projection = glm::perspective(camera.GetZoom(), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		// use with perspective projection

		// Get their uniform location
		GLint modelLoc = glGetUniformLocation(shader.Program, "model");
		GLint viewLoc = glGetUniformLocation(shader.Program, "view");
		GLint projLoc = glGetUniformLocation(shader.Program, "projection");

		// Pass them to the shaders
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// ----------------------------------------------
		// draw a quad with texture
		// shape.drawTexturedQuad();
		cube.drawCube();

		//-----------------------------------------------------
		for (GLuint i = 0; i < 10; i++){
			// Calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//-----------------------------------------------------

		// Swap the screen buffers
		window.swapBuffers();
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return EXIT_SUCCESS;
}

// Moves/alters the camera positions based on user input
void DoMovement(){
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]){
		camera.ProcessKeyboard(FORWARD);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]){
		camera.ProcessKeyboard(BACKWARD);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]){
		camera.ProcessKeyboard(LEFT);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]){
		camera.ProcessKeyboard(RIGHT);
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024){
		if (action == GLFW_PRESS){
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE){
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos){
	if (firstMouse){
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}
