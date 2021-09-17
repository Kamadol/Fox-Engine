#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far)
	:m_fov(fov), m_aspectRatio(aspectRatio), m_near(near), m_far(far)
{
	m_projection = Mat4x4::perspective(fov, aspectRatio, near, far);
}

Mat4x4 PerspectiveCamera::getMatrix() const
{
	return Mat4x4::perspective(m_fov, m_aspectRatio, m_near, m_far) * getInvTransform();
}

void PerspectiveCamera::setFov(float fov)
{
	m_fov = fov;
}
float PerspectiveCamera::getFov() const
{
	return m_fov;
}
void PerspectiveCamera::setAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
}
float PerspectiveCamera::getAspectRatio() const
{
	return m_aspectRatio;
}
void PerspectiveCamera::setNear(float near)
{
	m_near = near;
}
float PerspectiveCamera::getNear() const
{
	return m_near;
}
void PerspectiveCamera::setFar(float far)
{
	m_far = far;
}
float PerspectiveCamera::getFar() const
{
	return m_far;
}
