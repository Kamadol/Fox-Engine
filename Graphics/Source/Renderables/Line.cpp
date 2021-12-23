#include "Line.hpp"

Line::Line()
	:m_thickness(0.0f), m_color(Vector4(0.0f, 0.0f, 0.0f, 1.0f)), m_fillGaps(true)
{

}

void Line::addPoint(Vector3 point)
{
	m_points.push_back(point);
}
void Line::addPoints(std::vector<Vector3> points)
{
	m_points.reserve(m_points.size() + points.size());
	for (size_t i = 0; i < m_points.size(); i++)
	{
		m_points.push_back(points[i]);
	}
}
