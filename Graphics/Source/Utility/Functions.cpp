#include "Functions.hpp"

bool containsPoint(Vec2i position, Vec2i size, Vec2i point)
{
	if (point.x >= position.x && point.x <= position.x + size.x)
	{
		if (point.y >= position.y && point.y <= position.y + size.y)
		{
			return true;
		}
	}

	return false;
}
