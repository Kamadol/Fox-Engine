#include "Transformable.hpp"

Transformable::Transformable()
	:m_position(Vector3(0.0f, 0.0f, 0.0f)), m_scale(Vector3(1.0f, 1.0f, 1.0f)), m_rotation(Quaternion())
{

}

Mat4x4 Transformable::getTransform() const
{
	return Mat4x4::translation(m_position) * m_rotation.toMatrix() * Mat4x4::scale(m_scale);
}
Mat4x4 Transformable::getInvTransform() const
{
	return Mat4x4::scale(Vector3(1.0f / m_scale.x, 1.0f / m_scale.y, 1.0f / m_scale.z)) * m_rotation.conj().toMatrix() * Mat4x4::translation(-m_position);
}

void Transformable::setPosition(Vector3 position)
{
	m_position = position;
}
void Transformable::move(Vector3 offset)
{
	m_position += offset;
}
Vector3 Transformable::getPosition() const
{
	return m_position;
}

void Transformable::setScale(Vector3 scale)
{
	m_scale = scale;
}
void Transformable::scale(Vector3 scale)
{
	m_scale.x *= scale.x;
	m_scale.y *= scale.y;
	m_scale.z *= scale.z;
}
Vector3 Transformable::getScale() const
{
	return m_scale;
}

void Transformable::setRotation(Quaternion rotation)
{
	m_rotation = rotation;
}
void Transformable::rotate(Quaternion rotation)
{
	m_rotation *= rotation;
}
void Transformable::rotate(Vector3 axis, float angle)
{
	m_rotation *= Quaternion(axis, angle);
}
Quaternion Transformable::getRotation() const
{
	return m_rotation;
}

Vector3 Transformable::getRight() const
{
	return m_rotation.rotate(Vector3(1.0f, 0.0f, 0.0f));
}
Vector3 Transformable::getUp() const
{
	return m_rotation.rotate(Vector3(0.0f, 1.0f, 0.0f));
}
Vector3 Transformable::getFront() const
{
	return m_rotation.rotate(Vector3(0.0f, 0.0f, 1.0f));
}
