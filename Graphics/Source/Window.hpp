#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window
{
public:
	Window(size_t width, size_t height);
	~Window();

	bool isOpen() const;
	void close();
	void setShouldClose(bool shouldClose);
	bool shouldClose();

	void clear();
	void pollEvents();
	void swapBuffers();

	float getAspectRatio();

private:
	size_t m_width, m_height;

	GLFWwindow* m_window;

private:

};

#endif
