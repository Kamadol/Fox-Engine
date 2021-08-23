#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include "Vector3.hpp"
#include "Mat4x4.hpp"
#include "Quaternion.hpp"

class Transformable
{
public:
	Transformable();

	Mat4x4 getTransform() const;
	Mat4x4 getInvTransform() const;

	void setPosition(Vector3 position);
	void move(Vector3 offset);
	Vector3 getPosition() const;

	void setScale(Vector3 scale);
	void scale(Vector3 scale);
	Vector3 getScale() const;

	void setRotation(Quaternion rotation);
	void rotate(Quaternion rotation);
	void rotate(Vector3 axis, float angle);
	Quaternion getRotation() const;

protected:
	Vector3 m_position;
	Vector3 m_scale;
	Quaternion m_rotation;

};

#endif