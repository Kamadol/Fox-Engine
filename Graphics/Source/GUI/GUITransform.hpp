#ifndef GUI_TRANSFORM_HPP
#define GUI_TRANSFORM_HPP

#include "Vector2.hpp"

#define TOP_BORDER 3.0f
#define RIGHT_BORDER 3.0f
#define BOTTOM_BORDER 3.0f
#define LEFT_BORDER 3.0f

class GUITransform
{
public:
	GUITransform();

private:
	Vector2 m_position;
	size_t m_xSize, m_ySize;

private:
	GUITransform* m_parent;
	GUITransform* m_up;
	GUITransform* m_right;
	GUITransform* m_down;
	GUITransform* m_left;

};

#endif
