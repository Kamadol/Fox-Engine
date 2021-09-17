#include "GradientMask.hpp"

#include <iostream>

#include "Utility/Utility.hpp"

pg::GradientMask::GradientMask(float x0, float y0, float x1, float y1, bool vertical)
	:m_x0(x0), m_y0(y0), m_x1(x1), m_y1(y1), m_vertical(vertical)
{

}

float pg::GradientMask::getValue(float x, float y)
{
	/*if (m_vertical)
	{
		if (y < m_y0)
			return 0.0f;
		else if(y > m_y1)
			return 1.0f;
		else
			return (y - m_y0) / (m_y1 - m_y0);
	}
	else
	{
		if (x < m_x0)
			return 0.0f;
		else if (x > m_x1)
			return 1.0f;
		else
			return (x - m_x0) / (m_x1 - m_x0);
	}*/

	float vecX0X1 = m_x1 - m_x0;
	float vecY0X1 = m_y1 - m_y0;

	float vecXX0 = m_x0 - x;
	float vecYY0 = m_y0 - y;

	float vecXX1 = m_x1 - x;
	float vecYY1 = m_y1 - y;

	//TODO
	//gradient that works in any direction

	/*if ()
	{

	}*/

	return 0.0f;
}
