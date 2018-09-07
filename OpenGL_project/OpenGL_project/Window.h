#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

struct Keys {
	bool W;
	bool A;
	bool S;
	bool D;
	bool Q;
	bool E;
	bool UP;
	bool DOWN;
	bool LEFT;
	bool RIGHT;

	Keys() {
		reset();
	}

	void reset() {
		W = false;
		A = false;
		S = false;
		D = false;
		Q = false;
		E = false;
		UP = false;
		DOWN = false;
		LEFT = false;
		RIGHT = false;
	}
};

class Window
{
private:
	const GLuint windowWidth;
	const GLuint windowHeight;
	const char *windowName;
	GLFWwindow *window;
	Keys keys;
public:
	Window(const GLuint width, const GLuint height, const char *name);
	const GLuint getWindowWidth() { return windowWidth; }
	const GLuint getWindowHeight() { return windowHeight; }
	const char* getWindowName(){ return windowName; }
	GLFWwindow* getWindow() { return window; }
	int exitFailure();
	bool isNotClosed();
	void swapBuffers();
	int keyPressed();
	void resetKeys();
	~Window();
};
