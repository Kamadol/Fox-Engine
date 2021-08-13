#ifndef INPUT_HPP
#define INPUT_HPP

#include "Window.hpp"
#include "Vector2.hpp"

enum KEY
{
	SPACE = GLFW_KEY_SPACE,
	ESC = GLFW_KEY_ESCAPE,
	LSHIFT = GLFW_KEY_LEFT_SHIFT,
	RSHIFT = GLFW_KEY_RIGHT_SHIFT,
	A = GLFW_KEY_A,
	B = GLFW_KEY_B,
	C = GLFW_KEY_C,
	D = GLFW_KEY_D,
	E = GLFW_KEY_E,
	F = GLFW_KEY_F,
	G = GLFW_KEY_G,
	H = GLFW_KEY_H,
	I = GLFW_KEY_I,
	J = GLFW_KEY_J,
	K = GLFW_KEY_K,
	L = GLFW_KEY_L,
	M = GLFW_KEY_M,
	N = GLFW_KEY_N,
	O = GLFW_KEY_O,
	P = GLFW_KEY_P,
	Q = GLFW_KEY_Q,
	R = GLFW_KEY_P,
	S = GLFW_KEY_S,
	T = GLFW_KEY_T,
	U = GLFW_KEY_U,
	V = GLFW_KEY_V,
	W = GLFW_KEY_W,
	X = GLFW_KEY_X,
	Y = GLFW_KEY_Y,
	Z = GLFW_KEY_Z,
};
class Input
{
	friend Window;

public:
	Input();

	static bool isButtonPressed(int code);
	static bool isMouseButtonPressed(int code);
	static Vector2 getMousePosition();
	static void setMouseStartPosition(Vector2 startMousePosition);
	static Vector2 getMouseMovement();

private:
	static bool m_keys[GLFW_KEY_LAST];
	static bool m_mouseButtons[GLFW_MOUSE_BUTTON_LAST];
	static bool firstMouse;
	static Vector2 m_previousMousePosition;
	static Vector2 m_mousePosition;

private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

};

#endif
