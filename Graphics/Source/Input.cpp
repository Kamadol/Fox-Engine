#include "Input.hpp"

#include <iostream>

bool Input::m_keys[GLFW_KEY_LAST];
bool Input::m_singlePressKeys[GLFW_KEY_LAST];
bool Input::m_isSinglePress[GLFW_KEY_LAST];

bool Input::m_mouseButtons[GLFW_MOUSE_BUTTON_LAST];
bool Input::m_isSingleMousePress[GLFW_MOUSE_BUTTON_LAST];
bool Input::firstMouse = true;
Vector2 Input::m_previousMousePosition;
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
bool Input::isButtonOncePressed(int code)
{
	if (isButtonPressed(code) && !m_isSinglePress[code])
	{
		m_isSinglePress[code] = 1;
		return 1;
	}
	if (!isButtonPressed(code))
	{
		m_isSinglePress[code] = 0;
		return 0;
	}

	return 0;
}

bool Input::isMouseButtonPressed(int code)
{
	return m_mouseButtons[code];
}
bool Input::isMouseButtonOncePressed(int code)
{
	if (isMouseButtonPressed(code) && !m_isSingleMousePress[code])
	{
		m_isSingleMousePress[code] = 1;
		return 1;
	}
	if (!isMouseButtonPressed(code))
	{
		m_isSingleMousePress[code] = 0;
		return 0;
	}

	return 0;
}
Vector2 Input::getMousePosition()
{
	return m_mousePosition;
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
