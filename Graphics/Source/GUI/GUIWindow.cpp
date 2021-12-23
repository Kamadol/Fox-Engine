#include "GUIWindow.hpp"

#include "Input.hpp"

#include "Utility/Functions.hpp"

//For body dragging
GUIWindow::DraggableBody::DraggableBody(GUIWindow* window)
{
	this->window = window;
}
void GUIWindow::DraggableBody::onClickInside()
{
	prevPosition = m_mousePosition;
}
void GUIWindow::DraggableBody::onClickMouseDown()
{
	Vec2i offset = m_mousePosition - prevPosition;

	window->move(offset);

	prevPosition = m_mousePosition;
}

//For corners dragging
GUIWindow::DraggableCorner::DraggableCorner(GUIWindow* window)
	:corner(0)
{
	this->window = window;
}
void GUIWindow::DraggableCorner::setMinMaxSize(Vec2i min, Vec2i max)
{
	this->min = min;
	this->max = max;
}
void GUIWindow::DraggableCorner::setCurrentCorner(uint16_t corner)
{
	this->corner = corner;
}
void GUIWindow::DraggableCorner::onClickInside()
{
	prevPosition = m_mousePosition;
}
void GUIWindow::DraggableCorner::onClickMouseDown()
{
	Vec2i offset = m_mousePosition - prevPosition;

	if (corner == 0)
	{
		window->move(Vec2i(0, offset.y));
		window->m_size = window->m_size - Vec2i(-offset.x, offset.y);
		for (size_t i = 0; i < window->m_children.size(); i++)
		{
			window->m_children[i]->move(Vec2i(0, -offset.y));
		}
	}
	else if (corner == 1)
	{
		window->move(offset);
		window->m_size = window->m_size - offset;
		for (size_t i = 0; i < window->m_children.size(); i++)
		{
			window->m_children[i]->move(-offset);
		}

		Vec2i pos = window->m_position;
		Vec2i size = window->m_size;
		if (size.x < min.x)
		{
			window->m_size.x = min.x;
		}
		/*else if (size.x > max.x)
		{
			window->m_corners[1].x = window->m_corners[3].x - max.x;
		}
		if (size.y < min.y)
		{
			window->m_corners[1].y = window->m_corners[3].y - min.y;
		}
		else if (size.y > max.y)
		{
			window->m_corners[1].y = window->m_corners[3].y - max.y;
		}*/
	}
	else if (corner == 2)
	{
		window->move(Vec2i(offset.x, 0));
		window->m_size = window->m_size - Vec2i(offset.x, -offset.y);
		for (size_t i = 0; i < window->m_children.size(); i++)
		{
			window->m_children[i]->move(Vec2i(-offset.x, 0));
		}
	}
	else if (corner == 3)
	{
		window->m_size = window->m_size + offset;
	}
	
	prevPosition = m_mousePosition;
}

GUIWindow* GUIWindow::m_currentDraggedWindow = nullptr;

GUIWindow::GUIWindow(Vec2i position, Vec2i size, Vec2i margin)
	:GUIRectangle(margin),
	m_bodyDrag(this),
	m_cornersDrag{ this, this, this, this }
{
	setPosition(position);
	setSize(size);

	for (size_t i = 0; i < 4; i++)
	{
		m_cornersDrag[i].setCurrentCorner(i);
		m_cornersDrag[i].setMinMaxSize(Vec2i(120, 120), Vec2i(400, 600));
	}
}

void GUIWindow::update()
{
	Vec2i margin = getMargin();
	Vec2i size = getSize();
	Vec2i worldPosition = getWorldPosition();

	Vector2 mousePos = Input::getMousePosition();
	Vec2i mousePosition = Vec2i(mousePos.x, mousePos.y);

	//m_bodyDrag.update(worldPosition + margin, m_corners[3] - m_corners[1] - margin * 2);
	m_bodyDrag.update(pointInBody(mousePosition));

	/*m_cornersDrag[0].update(worldPosition + Vec2i(size.x - margin.x, 0), margin);
	m_cornersDrag[1].update(worldPosition, margin);
	m_cornersDrag[2].update(worldPosition + Vec2i(0, size.y - margin.y), margin);
	m_cornersDrag[3].update(worldPosition + size - margin, margin);*/
	uint16_t corner = pointInCorner(mousePosition);
	if(corner == 1)
		m_cornersDrag[0].update(corner);
	else
		m_cornersDrag[0].update(false);

	if(corner == 2)
		m_cornersDrag[1].update(corner);
	else
		m_cornersDrag[1].update(false);

	if (corner == 3)
		m_cornersDrag[2].update(corner);
	else
		m_cornersDrag[2].update(false);

	if (corner == 4)
		m_cornersDrag[3].update(corner);
	else
		m_cornersDrag[3].update(false);
}
