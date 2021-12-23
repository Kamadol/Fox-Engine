#ifndef GUI_TRANSFORM_HPP
#define GUI_TRANSFORM_HPP

#include <vector>

#include "Utility/Vec2.hpp"

class GUITransform
{
public:
	GUITransform(Vec2i position, Vec2i size);
	GUITransform();

	void addChildren(GUITransform* children);

	//Point in global gui space
	bool contains(Vec2i point);

	void setPosition(Vec2i position);
	void setWorldPosition(Vec2i position);
	void move(Vec2i offset);
	Vec2i getLocalPosition() const;
	Vec2i getWorldPosition() const;

	void setSize(Vec2i size);
	Vec2i getSize() const;

protected:
	Vec2i m_position;
	Vec2i m_size;

protected:
	GUITransform* m_parent;
	std::vector<GUITransform*> m_children;

};

#endif
