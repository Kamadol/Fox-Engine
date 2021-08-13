#ifndef ORTHOGRAPHIC_CAMERA_HPP
#define ORTHOGRAPHIC_CAMERA_HPP

#include "Camera.hpp"
#include "Transformable.hpp"

class OrthographicCamera : public Camera, public Transformable
{
public:
	OrthographicCamera(float left, float right, float bottom, float top, float near, float far);

	virtual Mat4x4 getMatrix() override;

};

#endif
