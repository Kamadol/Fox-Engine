#include "Draggable.hpp"

#include "Input.hpp"
#include "Functions.hpp"

Draggable::Draggable()
	:m_clicked(false), m_released(false), m_clickedInside(false)
{

}

void Draggable::update(Vec2i position, Vec2i size, Vec2i point)
{
	Vector2 mousePos = Input::getMousePosition();
	m_mousePosition = Vec2i(mousePos.x, mousePos.y);

	bool leftClick = Input::isMouseButtonPressed(MOUSE_KEY::LEFT);

	if (leftClick)
	{
		if (!m_clicked)
		{
			if (containsPoint(position, size, point))
			{
				onClickInside();
				m_clickedInside = true;
			}
			else
			{
				onClickOutside();
			}
			onClick();
			m_clicked = true;
		}

		if (m_clickedInside)
		{
			onClickMouseDown();
		}

		m_released = true;
	}
	else
	{
		if (m_released)
		{
			onRelease();
			m_released = false;
		}
		m_clicked = false;
		m_clickedInside = false;
	}
}
void Draggable::update(bool contains)
{
	Vector2 mousePos = Input::getMousePosition();
	m_mousePosition = Vec2i(mousePos.x, mousePos.y);

	bool leftClick = Input::isMouseButtonPressed(MOUSE_KEY::LEFT);

	if (leftClick)
	{		
		if (!m_clicked)
		{
			if (contains)
			{
				onClickInside();
				m_clickedInside = true;
			}
			else
			{
				onClickOutside();
			}
			onClick();
			m_clicked = true;
		}

		if (m_clickedInside)
		{
			onClickMouseDown();
		}

		m_released = true;
	}
	else
	{
		if (m_released)
		{
			onRelease();
			m_released = false;
		}
		m_clicked = false;
		m_clickedInside = false;
	}
}

void Draggable::onClick()
{

}
void Draggable::onClickInside()
{

}
void Draggable::onClickOutside()
{

}
void Draggable::onClickMouseDown()
{

}
void Draggable::onRelease()
{

}
