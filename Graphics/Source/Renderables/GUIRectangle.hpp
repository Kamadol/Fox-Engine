#ifndef GUI_RECTANGLE_HPP
#define GUI_RECTANGLE_HPP

#include <stdint.h>

#include "GUI/GUITransform.hpp"

class GUIRectangle : public GUITransform
{
public:
	GUIRectangle(Vec2i margin);

	//Point is in gui space. If we have point in other space we must change it to gui space.
	bool pointInBody(Vec2i point) const;
	uint16_t pointInCorner(Vec2i point) const; //1 - 4 from top-right, CCW. If 0 there is no collision.
	uint16_t pointInEdge(Vec2i point) const;   //1 - 4 from top, CCW. If 0 there is no collision.

	Vec2i getWorldTRPosition() const;
	Vec2i getWorldTLPosition() const;
	Vec2i getWorldDLPosition() const;
	Vec2i getWorldDRPosition() const;

	Vec2i getMargin() const;

private:
	Vec2i m_margin; //size of corners
	
};

#endif
