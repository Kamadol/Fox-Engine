#include "Utility.hpp"

Vector2 rotate(Vector2 v, float angle)
{
	float sPart = sinf(angle);
	float cPart = cosf(angle);

	return Vector2(v.x * cPart - v.y * sPart, v.x * sPart + v.y * cPart);
}
