#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include "Vector3.hpp"
#include "Mat4x4.hpp"

class Transformable
{
public:
	Transformable();

	Mat4x4 getTransform() const;

	void setPosition(Vector3 position);
	void move(Vector3 offset);
	Vector3 getPosition() const;

	void setScale(Vector3 scale);
	void scale(Vector3 scale);
	Vector3 getScale() const;

	void setRotation(Vector3 euler);
	void rotate(Vector3 offset);
	Vector3 getRotation() const;

protected:
	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_euler;

};

#endif
