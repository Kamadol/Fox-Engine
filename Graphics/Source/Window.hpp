#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Vector2.hpp"

class Window
{
public:
	Window(size_t width, size_t height);
	~Window();	

	static void wireFrameMode(bool mode);
	static void visibleCursor(bool mode);

	void makeCurrent();

	bool isOpen() const;
	void close();
	void setShouldClose(bool shouldClose);
	bool getShouldClose() const;

	void clear(bool color, bool depth, bool stencil);
	void clear();
	void pollEvents();
	void swapBuffers();

	Vector2 getSize() const;
	float getAspectRatio() const;

private:
	static void window_size_callback(GLFWwindow* window, int width, int height);

private:
	void init();

	GLFWwindow* m_window;

};

#endif
