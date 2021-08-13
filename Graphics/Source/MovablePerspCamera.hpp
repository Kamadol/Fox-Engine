#ifndef MOVABLE_PERSP_CAMERA_HPP
#define MOVABLE_PERSP_CAMERA_HPP

#include "Camera.hpp"
#include "Vector3.hpp"

class MovablePerspCamera : public Camera
{
public:
	MovablePerspCamera(float fov, float aspectRatio, float near, float far);

	void setPosition(Vector3 position);
	Vector3 getPosition();
	void move(Vector3 offset);
	void moveRight(float offset);
	void moveFront(float offset);

	void rotateX(float angle);
	void rotateY(float angle);

	void setFront(Vector3 front);
	void setUp(Vector3 up);

	virtual Mat4x4 getMatrix() override;

private:
	Vector3 m_position;
	Vector3 m_front;
	Vector3 m_up;

};

#endif
