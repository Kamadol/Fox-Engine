#include "Quaternion.hpp"

#include <cmath>

Quaternion::Quaternion(float w, float x, float y, float z)
	:w(w), x(x), y(y), z(z)
{

}
Quaternion::Quaternion(Vector3 axis, float angle)
{
	w = cosf(angle * 0.5f);
	x = axis.x * sinf(angle * 0.5f);
	y = axis.y * sinf(angle * 0.5f);
	z = axis.z * sinf(angle * 0.5f);
}
Quaternion::Quaternion()
	:w(1.0f), x(0.0f), y(0.0f), z(0.0f)
{

}

Quaternion Quaternion::conj() const
{
	return Quaternion(w, -x, -y, -z);
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
	ret.vals[2] = 2.0f * (x * z - w * y)       ; ret.vals[6] = 2.0f * (x * y - w * z)       ; ret.vals[10] = 2.0f * (w * w + z * z) - 1.0f; ret.vals[14] = 0.0f;
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

std::ostream& operator<<(std::ostream& end, const Quaternion& q)
{
	end << "(" << q.w << " " << q.x << " " << q.y << " " << q.z << ")";

	return end;
}