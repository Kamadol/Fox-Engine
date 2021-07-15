#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window
{
public:
	Window(size_t width, size_t height);

private:
	size_t m_width, m_height;

	GLFWwindow* m_window;

};

#endif
