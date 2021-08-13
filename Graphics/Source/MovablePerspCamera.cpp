#include "MovablePerspCamera.hpp"

MovablePerspCamera::MovablePerspCamera(float fov, float aspectRatio, float near, float far)
{
	m_projection = Mat4x4::perspective(fov, aspectRatio, near, far);
}

void MovablePerspCamera::setPosition(Vector3 position)
{
	m_position = position;
}
Vector3 MovablePerspCamera::getPosition()
{
	return m_position;
}
void MovablePerspCamera::move(Vector3 offset)
{
	m_position += offset;
}
void MovablePerspCamera::moveRight(float offset)
{
	m_position += (m_front ^ m_up).unit() * offset;
}
void MovablePerspCamera::moveFront(float offset)
{
	m_position += m_front * offset;
}

void MovablePerspCamera::rotateX(float angle)
{
	Vector3 rotated = Mat4x4::rotation((m_front ^ m_up).unit(), angle) * m_front;
	if (abs((rotated.unit() * m_up.unit())) < 0.98f )
		m_front = Vector3(rotated.x, rotated.y, rotated.z);
}
void MovablePerspCamera::rotateY(float angle)
{
	m_front = Mat4x4::rotationY(angle) * m_front;
}

void MovablePerspCamera::setFront(Vector3 front)
{
	m_front = front;
}
void MovablePerspCamera::setUp(Vector3 up)
{
	m_up = up;
}

Mat4x4 MovablePerspCamera::getMatrix()
{
	return m_projection * Mat4x4::lookAt(m_position, m_position + m_front, m_up);
}
