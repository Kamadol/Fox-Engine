#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Mat4x4.hpp"

class Camera
{
public:
	virtual Mat4x4 getMatrix() = 0;

protected:
	Mat4x4 m_projection;

};

#endif
