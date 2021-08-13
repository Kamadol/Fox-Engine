#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Vector3.hpp"
#include "Mat4x4.hpp"

class Quaternion
{
public:
	Quaternion(float w, float x, float y, float z);
	Quaternion(Vector3 axis, float angle);
	Quaternion();

	Quaternion conj() const;
	 
	Vector3 toEuler() const;
	Mat4x4 toMatrix() const;
	Vector3 rotate(Vector3 v) const;

	Quaternion operator*(const Quaternion& q) const;
	Quaternion& operator*=(const Quaternion& q);

	friend std::ostream& operator<<(std::ostream& end, const Quaternion& q);

private:
	float w, x, y, z;

};

#endif
