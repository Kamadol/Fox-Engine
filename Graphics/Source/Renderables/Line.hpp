#ifndef LINE_HPP
#define LINE_HPP

#include <Vector>

#include "Transformable.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"

class Line : public Transformable
{
public:
	Line();

	void addPoint(Vector3 point);
	void addPoints(std::vector<Vector3> points);

public:
	std::vector<Vector3> m_points;
	float m_thickness;
	Vector4 m_color;
	bool m_fillGaps;

};

#endif
