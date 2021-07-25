#include "Transformable.hpp"

Transformable::Transformable()
	:m_position(Vector3(0.0f, 0.0f, 0.0f)), m_scale(Vector3(1.0f, 1.0f, 1.0f)), m_euler(Vector3(0.0f, 0.0f, 0.0f))
{

}

Mat4x4 Transformable::getTransform() const
{
	return Mat4x4::rotation(m_euler) * Mat4x4::scale(m_scale) * Mat4x4::translation(m_position);
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

void Transformable::setRotation(Vector3 euler)
{
	m_euler = euler;
}
void Transformable::rotate(Vector3 offset)
{
	m_euler += offset;
}
Vector3 Transformable::getRotation() const
{
	return m_euler;
}
