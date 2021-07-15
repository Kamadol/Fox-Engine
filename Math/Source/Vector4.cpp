#include "Vector4.hpp"

Vector4::Vector4(float x, float y, float z, float w)
	:x(x), y(y), z(z), w(w)
{

}
Vector4::Vector4()
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{

}

Vector4 Vector4::zero()
{
	return Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}
Vector4 Vector4::right()
{
	return Vector4(1.0f, 0.0f, 0.0f, 1.0f);
}
Vector4 Vector4::left()
{
	return Vector4(-1.0f, 0.0f, 0.0f, 1.0f);
}
Vector4 Vector4::up()
{
	return Vector4(0.0f, 1.0f, 0.0f, 1.0f);
}
Vector4 Vector4::down()
{
	return Vector4(0.0f, -1.0f, 0.0f, 1.0f);
} 
Vector4 Vector4::front()
{
	return Vector4(0.0f, 0.0f, 1.0f, 1.0f);
}
Vector4 Vector4::back()
{
	return Vector4(0.0f, 0.0f, -1.0f, 1.0f);
}

Vector4 Vector4::multiplyElements(const Vector4& v)
{
	return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
}
Vector4 Vector4::divideElements(const Vector4& v)
{
	return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
}
float Vector4::dot(const Vector4& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}
Vector4& Vector4::operator-=(const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}
Vector4 Vector4::operator+(const Vector4& v) const
{
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}
Vector4 Vector4::operator-(const Vector4& v) const
{
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}
float Vector4::operator*(const Vector4& v) const
{
	return x * v.x + y * v.y + z * v.z;
}
Vector4 Vector4::operator*(float a) const
{
	return Vector4(x * a, y * a, z * a, w * a);
}
Vector4 Vector4::operator/(float a) const
{
	return Vector4(x / a, y / a, z / a, w / a);
}

std::ostream& operator<<(std::ostream& end, const Vector4& v)
{
	end << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return end;
}
