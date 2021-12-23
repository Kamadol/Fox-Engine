#include "GUIRectangle.hpp"

#include "Utility/Functions.hpp"

GUIRectangle::GUIRectangle(Vec2i margin)
	:m_margin(margin)
{

}

bool GUIRectangle::pointInBody(Vec2i point) const
{
	return containsPoint(getWorldPosition() + m_margin, m_size - m_margin * 2.0f, point);
}
uint16_t GUIRectangle::pointInCorner(Vec2i point) const
{
	Vec2i globalPoint = getWorldPosition();

	if (containsPoint(Vec2i(globalPoint.x + m_size.x - m_margin.x, globalPoint.y), m_margin, point))
		return 1;
	if (containsPoint(globalPoint, m_margin, point))
		return 2;
	if (containsPoint(Vec2i(globalPoint.x, globalPoint.y + m_size.y - m_margin.y), m_margin, point))
		return 3;
	if (containsPoint(globalPoint + m_size - m_margin, m_margin, point))
		return 4;

	return 0;
}
uint16_t GUIRectangle::pointInEdge(Vec2i point) const
{
	Vec2i globalPoint = getWorldPosition();

	if (containsPoint(Vec2i(globalPoint.x + m_margin.x, globalPoint.y), Vec2i(m_size.y - m_margin.y * 2.0, m_margin.y), point))
		return 1;
	if (containsPoint(Vec2i(globalPoint.x, globalPoint.y + m_margin.y), Vec2i(m_margin.x, m_size.y - m_margin.y * 2.0), point))
		return 2;
	if (containsPoint(Vec2i(globalPoint.x + m_margin.x, globalPoint.y + m_size.y - m_margin.y), Vec2i(m_size.x - m_margin.y * 2.0, m_margin.y), point))
		return 3;
	if (containsPoint(Vec2i(globalPoint.x + m_size.x - m_margin.x, globalPoint.y + m_margin.y), Vec2i(m_margin.x, m_size.y - m_margin.y * 2.0), point))
		return 4;

	return 0;
}

Vec2i GUIRectangle::getWorldTRPosition() const
{
	return getWorldPosition() + Vec2i(m_size.x, 0);
}
Vec2i GUIRectangle::getWorldTLPosition() const
{
	return getWorldPosition();
}
Vec2i GUIRectangle::getWorldDLPosition() const
{
	return getWorldPosition() + Vec2i(0, m_size.y);
}
Vec2i GUIRectangle::getWorldDRPosition() const
{
	return getWorldPosition() + m_size;
}

Vec2i GUIRectangle::getMargin() const
{
	return m_margin;
}
