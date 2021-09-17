#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
	:m_left(left), m_right(right), m_bottom(bottom), m_top(top), m_near(near), m_far(far)
{
	m_projection = Mat4x4::orthographic(left, right, bottom, top, near, far);
}

Mat4x4 OrthographicCamera::getMatrix() const
{
	return getInvTransform() * Mat4x4::orthographic(m_left, m_right, m_bottom, m_top, m_near, m_far);
}

void OrthographicCamera::setLeft(float left)
{
	m_left = left;
}
float OrthographicCamera::getLeft() const
{
	return m_left;
}
void OrthographicCamera::setRight(float right)
{
	m_right = right;
}
float OrthographicCamera::getRight() const
{
	return m_right;
}
void OrthographicCamera::setTop(float top)
{
	m_top = top;
}
float OrthographicCamera::getTop() const
{
	return m_top;
}
void OrthographicCamera::setBottom(float bottom)
{
	m_bottom = bottom;
}
float OrthographicCamera::getBottom() const
{
	return m_bottom;
}
void OrthographicCamera::setNear(float near)
{
	m_near = near;
}
float OrthographicCamera::getNear() const
{
	return m_near;
}
void OrthographicCamera::setFar(float far)
{
	m_far = far;
}
float OrthographicCamera::getFar() const
{
	return m_far;
}
