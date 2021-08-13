#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far)
{
	m_projection = Mat4x4::perspective(fov, aspectRatio, near, far);
}

Mat4x4 PerspectiveCamera::getMatrix()
{
	return m_projection * getInvTransform();
}
