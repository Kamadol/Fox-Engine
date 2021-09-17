#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "Vector3.hpp"
#include "Mat4x4.hpp"

class Quaternion
{
public:
	Quaternion(Vector3 axis, float angle);
	Quaternion();

	static Quaternion identity();

	Quaternion conj() const;
	float dot(Quaternion other) const;	
	 
	Vector3 toEuler() const;
	Mat4x4 toMatrix() const;
	Vector3 rotate(Vector3 v) const;
	Quaternion lerp(Quaternion other, float a);
	Quaternion slerp(Quaternion other, float a);

	Quaternion operator*(const Quaternion& q) const;
	Quaternion& operator*=(const Quaternion& q);

	friend std::ostream& operator<<(std::ostream& end, const Quaternion& q);

private:
	float w, x, y, z;

private:
	Quaternion(float w, float x, float y, float z);

	float selfDot() const;
	float length() const;
	Quaternion unit() const;
	Quaternion operator+(const Quaternion& q) const;
	Quaternion operator-(const Quaternion& q) const;
	Quaternion operator*(float a) const;
	Quaternion operator/(float a) const;

};

#endif
