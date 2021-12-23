#ifndef DRAGGABLE_HPP
#define DRAGGABLE_HPP

#include "Vec2.hpp"

class Draggable
{
public:
	Draggable();

	void update(Vec2i position, Vec2i size, Vec2i point);
	void update(bool contains);

	virtual void onClick();
	virtual void onClickInside();
	virtual void onClickOutside();
	virtual void onClickMouseDown();
	virtual void onRelease();

protected:
	Vec2i m_mousePosition;

private:
	bool m_clicked;
	bool m_released;
	bool m_clickedInside;

};

#endif
