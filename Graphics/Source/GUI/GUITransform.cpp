#include "GUITransform.hpp"

GUITransform::GUITransform(Vec2i position, Vec2i size)
	:m_position(position),
	m_size(size),
	m_parent(nullptr)
{

}
GUITransform::GUITransform()
	:m_position(0, 0),
	 m_size    (0, 0),
	 m_parent(nullptr)
{

}

void GUITransform::addChildren(GUITransform* children)
{
	children->m_parent = this;
	m_children.push_back(children);
}

bool GUITransform::contains(Vec2i point)
{
	Vec2i global = getWorldPosition();

	if (point.x > global.x && point.x < global.x + m_size.x)
	{
		if (point.y > global.y && point.y < global.y + m_size.y)
		{
			return true;
		}
	}

	return false;
}

void GUITransform::setPosition(Vec2i position)
{
	m_position = position;
}
void GUITransform::setWorldPosition(Vec2i position)
{
	m_position = position - m_parent->getWorldPosition();
}
void GUITransform::move(Vec2i offset)
{
	m_position += offset;
}
Vec2i GUITransform::getLocalPosition() const
{
	return m_position;
}
Vec2i GUITransform::getWorldPosition() const
{
	if (m_parent != nullptr)
		return m_position + m_parent->getWorldPosition();
	else
		return m_position;
}

void GUITransform::setSize(Vec2i size)
{
	m_size = size;
}
Vec2i GUITransform::getSize() const
{
	return m_size;
}
