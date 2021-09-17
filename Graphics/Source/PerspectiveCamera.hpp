#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "Camera.hpp"
#include "Transformable.hpp"

class PerspectiveCamera : public Camera, public Transformable
{
public:
	PerspectiveCamera(float fov, float aspectRatio, float near, float far);

	virtual Mat4x4 getMatrix() const override;

	void setFov(float fov);
	float getFov() const;
	void setAspectRatio(float aspectRatio);
	float getAspectRatio() const;
	void setNear(float near);
	float getNear() const;
	void setFar(float far);
	float getFar() const;

private:
	float m_fov;
	float m_aspectRatio;
	float m_near;
	float m_far;

};

#endif
