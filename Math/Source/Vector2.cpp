#include "Vector2.hpp"

Vector2::Vector2(float x, float y)
	:x(x), y(y)
{

}
Vector2::Vector2()
	:x(0.0f), y(0.0f)
{

}

Vector2 Vector2::zero()
{
	return Vector2(0.0f, 0.0f);
}
Vector2 Vector2::right()
{
	return Vector2(1.0f, 0.0f);
}
Vector2 Vector2::left()
{
	return Vector2(-1.0f, 0.0f);
}
Vector2 Vector2::up()
{
	return Vector2(0.0f, 1.0f);
}
Vector2 Vector2::down()
{
	return Vector2(0.0f, -1.0f);
}

float Vector2::length() const
{
	return sqrtf(x * x + y * y);
}
float Vector2::lengthSqr() const
{
	return x * x + y * y;
}
Vector2 Vector2::perpendicular() const
{
	return Vector2(-y, x);
}
Vector2 Vector2::rotate(float angle) const
{
	float sin = sinf(angle);
	float cos = cosf(angle);

	return Vector2(cos * x - sin * y, sin * x + cos * y);
}
Vector2 Vector2::unit() const
{
	return *this / length();
}
Vector2 Vector2::multiplyElementwise(const Vector2& v) const
{
	return Vector2(x * v.x, y * v.y);
}
Vector2 Vector2::divideElementwise(const Vector2& v) const
{
	return Vector2(x / v.x, y / v.y);
}
float Vector2::dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

Vector2& Vector2::operator*=(float a)
{
	x *= a;
	y *= a;

	return *this;
}
Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;

	return *this;
}
Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}
Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}
Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}
float Vector2::operator*(const Vector2& v) const
{
	return x * v.x + y * v.y;
}
Vector2 Vector2::operator*(float a) const
{
	return Vector2(x * a, y * a);
}
Vector2 Vector2::operator/(float a) const
{
	return Vector2(x / a, y / a);
}

bool Vector2::operator==(const Vector2& v) const
{
	return x == v.x && y == v.y;
}
bool Vector2::operator!=(const Vector2& v) const
{
	return x != v.x || y != v.y;
}

std::ostream& operator<<(std::ostream& end, const Vector2& v)
{
	end << "(" << v.x << ", " << v.y << ")";
	return end;
}
