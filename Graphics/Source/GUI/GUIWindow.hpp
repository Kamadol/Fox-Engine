#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include "Vector2.hpp"

class GUIWindow
{
public:
	GUIWindow();

	void update(Vector2 mousePosition, Vector2 screenSize);
	void draw();

private:
	Vector2 m_position;
	size_t m_xSize, m_ySize;

};

#endif
