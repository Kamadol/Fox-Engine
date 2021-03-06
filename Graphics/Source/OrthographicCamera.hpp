#ifndef ORTHOGRAPHIC_CAMERA_HPP
#define ORTHOGRAPHIC_CAMERA_HPP

#include "Camera.hpp"
#include "Transformable.hpp"

class OrthographicCamera : public Camera, public Transformable
{
public:
	OrthographicCamera(float left, float right, float bottom, float top, float near, float far);

	virtual Mat4x4 getMatrix() const override;

	void setLeft(float left);
	float getLeft() const;
	void setRight(float right);
	float getRight() const;
	void setTop(float top);
	float getTop() const;
	void setBottom(float bottom);
	float getBottom() const;
	void setNear(float near);
	float getNear() const;
	void setFar(float far);
	float getFar() const;

private:
	float m_left;
	float m_right;
	float m_bottom;
	float m_top;
	float m_near;
	float m_far;

};

#endif
