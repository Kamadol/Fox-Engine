#ifndef MOVABLE_PERSP_CAMERA_HPP
#define MOVABLE_PERSP_CAMERA_HPP

#include "Camera.hpp"
#include "Transformable.hpp"
#include "Vector3.hpp"

class MovablePerspCamera : public Camera, public Transformable
{
public:
	MovablePerspCamera(float fov, float aspectRatio, float near, float far);

	void update(float dTime);

	virtual Mat4x4 getMatrix() const override;

private:
	Quaternion m_currentRotation;

	float m_yAngle;
	float m_xAngle;

};

#endif
