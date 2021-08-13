#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <iostream>

class Vector3
{
public:
	Vector3(float x, float y, float z);
	Vector3();

	static Vector3 zero();
	static Vector3 right();
	static Vector3 left();
	static Vector3 up();
	static Vector3 down();
	static Vector3 front();
	static Vector3 back();

	float length() const;
	float lengthSqr() const;
	Vector3 unit() const;
	Vector3 multiplyElements(const Vector3& v) const;
	Vector3 divideElements(const Vector3& v) const;
	float dot(const Vector3& v) const;
	Vector3 cross(const Vector3& v) const;

	Vector3 operator-() const;
	Vector3& operator*=(float a);
	Vector3& operator/=(float a);
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3 operator+(const Vector3& v) const;
	Vector3 operator-(const Vector3& v) const;
	float operator*(const Vector3& v) const;
	Vector3 operator^(const Vector3& v) const;
	Vector3 operator*(float a) const;
	Vector3 operator/(float a) const;

	friend std::ostream& operator<<(std::ostream& end, const Vector3& v);

public:
	float x, y, z;

};

static Vector3 operator*(float a, const Vector3& v)
{
	return v * a;
}

#endif
