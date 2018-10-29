#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Camera.h"

class Window
{
private:
	const GLuint windowWidth;
	const GLuint windowHeight;
	const char *windowName;
	GLFWwindow *window;
	// Camera camera;
public:
	Window(const GLuint width, const GLuint height, const char *name);
	const GLuint getWindowWidth() { return windowWidth; }
	const GLuint getWindowHeight() { return windowHeight; }
	const char* getWindowName(){ return windowName; }
	GLFWwindow* getWindow() { return window; }
	// void setCamera(Camera c) {camera = c};
	int exitFailure();
	bool isNotClosed();
	void swapBuffers();
	
	~Window();
};
