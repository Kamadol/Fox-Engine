#include "Quaternion.hpp"

#include <cmath>

Quaternion::Quaternion(float w, float x, float y, float z)
	:w(w), x(x), y(y), z(z)
{

}
Quaternion::Quaternion(Vector3 axis, float angle)
{
	float sin = sinf(angle * 0.5f);

	w = cosf(angle * 0.5f);
	x = axis.x * sin;
	y = axis.y * sin;
	z = axis.z * sin;
}
Quaternion::Quaternion()
	:w(1.0f), x(0.0f), y(0.0f), z(0.0f)
{

}

Quaternion Quaternion::identity()
{
	return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
}

Quaternion Quaternion::conj() const
{
	return Quaternion(w, -x, -y, -z);
}
float Quaternion::selfDot() const
{
	return w * w + x * x + y * y + z * z;
}
float Quaternion::dot(Quaternion other) const
{
	return w * other.w + x * other.x + y * other.y + z * other.z;
}
float Quaternion::length() const
{
	return sqrtf(w * w + x * x + y * y + z * z);
}
Quaternion Quaternion::unit() const
{
	return (*this) / length();
}

Vector3 Quaternion::toEuler() const
{
	Vector3 ret;

	ret.x = atan2f(2.0f * (w * x + y * z), 1.0f - 2.0f * (x * x + y * y));
	ret.y = asinf(2.0f * (w * y - z * x));
	ret.x = atan2f(2.0f * (w * z + x * y), 1.0f - 2.0f * (y * y + z * z));

	return ret;
}
Mat4x4 Quaternion::toMatrix() const
{
	Mat4x4 ret;

	ret.vals[0] = 2.0f * (w * w + x * x) - 1.0f; ret.vals[4] = 2.0f * (x * y - w * z)       ; ret.vals[8]  = 2.0f * (x * z + w * y)       ; ret.vals[12] = 0.0f;
	ret.vals[1] = 2.0f * (x * y + w * z)       ; ret.vals[5] = 2.0f * (w * w + y * y) - 1.0f; ret.vals[9]  = 2.0f * (y * z - w * x)       ; ret.vals[13] = 0.0f;
	ret.vals[2] = 2.0f * (x * z - w * y)       ; ret.vals[6] = 2.0f * (y * z + w * x)       ; ret.vals[10] = 2.0f * (w * w + z * z) - 1.0f; ret.vals[14] = 0.0f;
	ret.vals[3] =                          0.0f; ret.vals[7] =                          0.0f; ret.vals[11] =                          0.0f; ret.vals[15] = 1.0f;

	return ret;
}
Vector3 Quaternion::rotate(Vector3 v) const
{
	//cannonical way
	//Quaternion qv = Quaternion(0.0f, v.x, v.y, v.z);
	//Quaternion result = (*this) * qv * conj();

	//return Vector3(result.x, result.y, result.z);


	Vector3 vPart(x, y, z);
	Vector3 tmp = 2.0f * vPart ^ v;

	return v + w * tmp + (vPart ^ tmp);
	//below gives bad result for some reason
	//return v + w * tmp + vPart ^ tmp;
}
Quaternion Quaternion::lerp(Quaternion other, float a)
{
	Quaternion lerped = ((*this) * (1.0f - a)) + (other * a);

	return lerped.unit();
}
Quaternion Quaternion::slerp(Quaternion other, float a)
{
	float halfAngle = acosf(((*this) * other.conj()).w);

	return (*this) * sinf((1.0f - a) * halfAngle) / sinf(halfAngle) + other * sinf(a * halfAngle) / sinf(halfAngle);
}

Quaternion Quaternion::operator+(const Quaternion& q) const
{
	return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
}
Quaternion Quaternion::operator-(const Quaternion& q) const
{
	return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
}
Quaternion Quaternion::operator*(const Quaternion& q) const
{
	Quaternion ret;

	ret.w = w * q.w - x * q.x - y * q.y - z * q.z;
	ret.x = w * q.x + x * q.w + y * q.z - z * q.y;
	ret.y = w * q.y - x * q.z + y * q.w + z * q.x;
	ret.z = w * q.z + x * q.y - y * q.x + z * q.w;

	return ret;
}
Quaternion& Quaternion::operator*=(const Quaternion& q)
{
	*this = *this * q;

	return *this;
}
Quaternion Quaternion::operator*(float a) const
{
	return Quaternion(w * a, x * a, y * a, z *a);
}
Quaternion Quaternion::operator/(float a) const
{
	return Quaternion(w / a, x / a, y / a, z / a);
}

std::ostream& operator<<(std::ostream& end, const Quaternion& q)
{
	end << "(" << q.w << " " << q.x << " " << q.y << " " << q.z << ")";

	return end;
}
