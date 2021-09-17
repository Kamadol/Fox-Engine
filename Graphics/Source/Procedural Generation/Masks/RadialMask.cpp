#include "RadialMask.hpp"

#include "Utility/Utility.hpp"

pg::RadialMask::RadialMask(float xCenter, float yCenter, float r, float R)
	:m_xCenter(xCenter), m_yCenter(yCenter), m_r(r), m_R(R)
{

}

float pg::RadialMask::getValue(float x, float y)
{
	float xDelta = x - m_xCenter;
	float yDelta = y - m_yCenter;
	float distanceSquared = xDelta * xDelta + yDelta * yDelta;

	if (distanceSquared < m_r * m_r)
	{
		return 1.0f;
	}
	else if (distanceSquared < m_R * m_R)
	{
		float weight = sqrtf(distanceSquared) - m_r;

		return lerp(1.0f, 0.0f, weight / (m_R - m_r));
	}
	else
		return 0.0f;
}
