#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>

class Vector2
{
public:
	Vector2(float x, float y);
	Vector2();

	static Vector2 zero();
	static Vector2 right();
	static Vector2 left();
	static Vector2 up();
	static Vector2 down();

	float length() const;
	float lengthSqr() const;
	Vector2 perpendicular() const;
	Vector2 rotate(float angle) const;
	Vector2 unit() const;
	Vector2 multiplyElementwise(const Vector2& v) const;
	Vector2 divideElementwise(const Vector2& v) const;
	float dot(const Vector2& v) const;

	Vector2& operator*=(float a);
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2 operator+(const Vector2& v) const;
	Vector2 operator-(const Vector2& v) const;
	float operator*(const Vector2& v) const;
	Vector2 operator*(float a) const;
	Vector2 operator/(float a) const;

	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;

	friend std::ostream& operator<<(std::ostream& end, const Vector2& v);

public:
	float x, y;

};

static Vector2 operator*(float a, const Vector2& v)
{
	return v * a;
}

#endif
