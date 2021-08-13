#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP

#include "Camera.hpp"
#include "Transformable.hpp"

class PerspectiveCamera : public Camera, public Transformable
{
public:
	PerspectiveCamera(float fov, float aspectRatio, float near, float far);

	virtual Mat4x4 getMatrix() override;

};

#endif
