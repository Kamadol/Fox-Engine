#include "Input.hpp"

#include <iostream>

bool Input::m_keys[GLFW_KEY_LAST];
bool Input::m_mouseButtons[GLFW_MOUSE_BUTTON_LAST];
bool Input::firstMouse = true;
Vector2 Input::m_previousMousePosition;// = Vector2(400.0f, 400.0f);
Vector2 Input::m_mousePosition;

Input::Input()
{
	for (size_t i = 0; i < GLFW_KEY_LAST; i++)
	{
		m_keys[i] = false;
	}
	for (size_t i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
	{
		m_mouseButtons[i] = false;
	}
}

bool Input::isButtonPressed(int code)
{
	return m_keys[code];
}
bool Input::isMouseButtonPressed(int code)
{
	return m_mouseButtons[code];
}
Vector2 Input::getMousePosition()
{
	return m_mousePosition;
}
void Input::setMouseStartPosition(Vector2 startMousePosition)
{
	m_previousMousePosition = startMousePosition;
}
Vector2 Input::getMouseMovement()
{
	if (m_mousePosition != Vector2::zero() && firstMouse)
	{
		m_previousMousePosition = m_mousePosition;
		firstMouse = false;
	}

	Vector2 ret = m_mousePosition - m_previousMousePosition;
	m_previousMousePosition = m_mousePosition;
	ret.y = -ret.y;

	return ret;
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	m_keys[key] = action != GLFW_RELEASE;

	//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		//glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	m_mouseButtons[button] = action != GLFW_RELEASE;
}
void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	m_mousePosition.x = xpos;
	m_mousePosition.y = ypos;
}
