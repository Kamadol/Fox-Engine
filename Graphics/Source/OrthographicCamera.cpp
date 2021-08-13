#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
{
	m_projection = Mat4x4::orthographic(left, right, bottom, top, near, far);
}

Mat4x4 OrthographicCamera::getMatrix()
{
	return getInvTransform() * m_projection;
}
