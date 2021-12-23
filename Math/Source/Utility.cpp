#include "Utility.hpp"

Vector2 rotate(Vector2 v, float angle)
{
	float sPart = sinf(angle);
	float cPart = cosf(angle);

	return Vector2(v.x * cPart - v.y * sPart, v.x * sPart + v.y * cPart);
}

Vector2 cubicBezier2D(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t)
{
	float t2 = t * t;
	float t3 = t2 * t;

	Vector2 a = p1 * (	  -t3 + 3 * t2 - 3 * t + 1);
	Vector2 b = p2 * ( 3 * t3 - 6 * t2 + 3 * t	  );
	Vector2 c = p3 * (-3 * t3 + 3 * t2			  );
	Vector2 d = p4 * (	   t3					  );

	return a + b + c + d;
}
Vector2 cubicBezierDeriv2D(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t)
{
	float t2 = t * t;

	Vector2 a = p1 * (-3 * t2 +  6 * t - 3);
	Vector2 b = p2 * ( 9 * t2 - 12 * t + 3);
	Vector2 c = p3 * (-9 * t2 +  6 * t	  );
	Vector2 d = p4 * ( 3 * t2			  );

	return a + b + c + d;
}
Vector2 cubicBezierDDeriv2D(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t)
{
	Vector2 a = p1 * ( -6 * t +  6);
	Vector2 b = p2 * ( 18 * t - 12);
	Vector2 c = p3 * (-18 * t +  6);
	Vector2 d = p4 * (  6 * t	  );

	return a + b + c + d;
}
Vector3 cubicBezier3D(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, float t)
{
	float t2 = t * t;
	float t3 = t2 * t;

	Vector3 a = p1 * (	  -t3 + 3 * t2 - 3 * t + 1);
	Vector3 b = p2 * ( 3 * t3 - 6 * t2 + 3 * t	  );
	Vector3 c = p3 * (-3 * t3 + 3 * t2			  );
	Vector3 d = p4 * (	   t3					  );

	return a + b + c + d;
}
