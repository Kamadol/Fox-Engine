#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include <iostream>

class Vector4
{
public:
	Vector4(float x, float y, float z, float w);
	Vector4();

	static Vector4 zero();
	static Vector4 right();
	static Vector4 left();
	static Vector4 up();
	static Vector4 down();
	static Vector4 front();
	static Vector4 back();

	Vector4 multiplyElements(const Vector4& v);
	Vector4 divideElements(const Vector4& v);
	float dot(const Vector4& v);

	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4 operator+(const Vector4& v) const;
	Vector4 operator-(const Vector4& v) const;
	float operator*(const Vector4& v) const;
	Vector4 operator*(float a) const;
	Vector4 operator/(float a) const;

	friend std::ostream& operator<<(std::ostream& end, const Vector4& v);

public:
	float x, y, z, w;

};

static Vector4 operator*(float a, const Vector4& v)
{
	return v * a;
}

#endif
