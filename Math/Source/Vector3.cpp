#include "Vector3.hpp"

Vector3::Vector3(float x, float y, float z)
	:x(x), y(y), z(z)
{

}
Vector3::Vector3(float xyz)
	:x(xyz), y(xyz), z(xyz)
{

}
Vector3::Vector3()
	: x(0.0f), y(0.0f), z(0.0f)
{

}

Vector3 Vector3::zero()
{
	return Vector3(0.0f, 0.0f, 0.0f);
}
Vector3 Vector3::right()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}
Vector3 Vector3::left()
{
	return Vector3(-1.0f, 0.0f, 0.0f);
}
Vector3 Vector3::up()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}
Vector3 Vector3::down()
{
	return Vector3(0.0f, -1.0f, 0.0f);
}
Vector3 Vector3::front()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}
Vector3 Vector3::back()
{
	return Vector3(0.0f, 0.0f, -1.0f);
}

float Vector3::length() const
{
	return sqrtf(x * x + y * y + z * z);
}
float Vector3::lengthSqr() const
{
	return x * x + y * y + z * z;
}
Vector3 Vector3::unit() const
{
	return *this / length();
}
Vector3 Vector3::multiplyElements(const Vector3& v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}
Vector3 Vector3::divideElements(const Vector3& v) const
{
	return Vector3(x / v.x, y / v.y, z / v.z);
}
float Vector3::dot(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}
Vector3 Vector3::cross(const Vector3& v) const
{
	return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}
Vector3& Vector3::operator*=(float a)
{
	x *= a;
	y *= a;
	z *= a;

	return *this;
}
Vector3& Vector3::operator/=(float a)
{
	x /= a;
	y /= a;
	z /= a;

	return *this;
}
Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}
Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}
Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}
Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}
float Vector3::operator*(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}
Vector3 Vector3::operator^(const Vector3& v) const
{
	return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}
Vector3 Vector3::operator*(float a) const
{
	return Vector3(x * a, y * a, z * a);
}
Vector3 Vector3::operator/(float a) const
{
	return Vector3(x / a, y / a, z / a);
}

std::ostream& operator<<(std::ostream& end, const Vector3& v)
{
	end << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return end;
}
