#include "Window.hpp"

#include <iostream>

#include "Input.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

void Window::window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, width);
}

size_t Window::m_windowCount = 0;

Window::Window(size_t width, size_t height)
{
	init();

	m_window = glfwCreateWindow(width, height, "Fox Engine", NULL, NULL);
	//m_window = glfwCreateWindow(width, height, "Fox Engine", glfwGetPrimaryMonitor(), NULL);
	if (!m_window)
	{
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_window);

	//opengl init
	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initialize GLEW" << std::endl;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	m_windowCount++;

	//some flags and window stuff inits
	glfwSwapInterval(1);
	glfwSetWindowPos(m_window, 400, 100);

	glfwSetKeyCallback(m_window, Input::key_callback);
	glfwSetMouseButtonCallback(m_window, Input::mouse_button_callback);
	glfwSetCursorPosCallback(m_window, Input::cursor_position_callback);

	glfwSetWindowSizeCallback(m_window, window_size_callback);

	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.1f, 0.3f, 1.0f, 1.0f);
}
Window::~Window()
{
	glfwDestroyWindow(m_window);

	m_windowCount--;
	if (m_windowCount == 0)
		glfwTerminate();
}

void Window::init()
{
	if (!glfwInit())
	{
		std::cout << "failed to initialize GLFW" << std::endl;
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::makeCurrent()
{
	glfwMakeContextCurrent(m_window);
}

bool Window::isOpen() const
{
	return glfwWindowShouldClose(m_window);
}
void Window::close()
{
	glfwDestroyWindow(m_window);
}
void Window::setShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(m_window, shouldClose);
}
bool Window::getShouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

void Window::clear(bool color, bool depth, bool stencil)
{
	if (color)
		glClear(GL_COLOR_BUFFER_BIT);
	if (depth)
		glClear(GL_DEPTH_BUFFER_BIT);
	if (stencil)
		glClear(GL_STENCIL_BUFFER_BIT);
}
void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
void Window::pollEvents()
{
	glfwPollEvents();
}
void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

Vector2 Window::getSize() const
{
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	return Vector2((float)width, (float)height);
}
float Window::getAspectRatio() const
{
	Vector2 size = getSize();

	return size.x / size.y;
}
