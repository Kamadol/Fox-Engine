#ifndef MAT4X4_HPP
#define MAT4X4_HPP

#include <iostream>

#include "Vector3.hpp"
#include "Vector4.hpp"

/*
|0 4  8 12|
|1 5  9 13|
|2 6 10 14|
|3 7 11 15|
*/

class Mat4x4
{
public:
	Mat4x4(float v);
	Mat4x4();

	static Mat4x4 diagonal(float diagonal);
	static Mat4x4 identity();
	static Mat4x4 translation(const Vector3& v);
	static Mat4x4 rotation(const Vector3& axis, float angle);
	static Mat4x4 rotation(const Vector3& eulerXYZ);
	static Mat4x4 rotationX(float angle);
	static Mat4x4 rotationY(float angle);
	static Mat4x4 rotationZ(float angle);
	static Mat4x4 scale(const Vector3& v);
	static Mat4x4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static Mat4x4 perspective(float fov, float aspectRatio, float near, float far);

	Mat4x4 operator+(const Mat4x4& m);
	Mat4x4 operator-(const Mat4x4& m);
	Mat4x4 operator*(const Mat4x4& m);
	Mat4x4 operator*(float a);
	Mat4x4 operator/(float a);

	Vector3 operator*(const Vector3& v);
	Vector4 operator*(const Vector4& v);

	Mat4x4& operator+=(const Mat4x4& m);
	Mat4x4& operator-=(const Mat4x4& m);
	Mat4x4& operator*=(const Mat4x4& m);
	Mat4x4& operator*=(float a);
	Mat4x4& operator/=(float a);

	float& operator()(size_t x, size_t y);

	friend std::ostream& operator<<(std::ostream& end, const Mat4x4& m);

public:
	union
	{
		float vals[16];
		Vector4 columns[4];
	};

};

#endif
