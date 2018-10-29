#include "Window.h"


Window::Window(const GLuint width, const GLuint height, const char *name)
	:windowWidth(width),windowHeight(height),windowName(name)
{
	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	this->window = glfwCreateWindow(windowWidth, windowHeight, windowName, nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		exitFailure();
	}

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(this->window, &screenWidth, &screenHeight);
	glfwMakeContextCurrent(this->window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		
		exitFailure();
	}

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);
	// enable depth support for 3d graphics
	glEnable(GL_DEPTH_TEST);
	// enable alpha support for image format like png
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int Window::exitFailure() {
	return EXIT_FAILURE;
}

bool Window::isNotClosed() {
	return !glfwWindowShouldClose(this->window);
}

void Window::swapBuffers() {
	glfwSwapBuffers(this->window);
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
}
