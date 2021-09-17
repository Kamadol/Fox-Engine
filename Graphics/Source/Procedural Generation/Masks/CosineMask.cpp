#include "CosineMask.hpp"

pg::CosineMask::CosineMask(float posX, float posY, float period)
	:m_posX(posX), m_posY(posY)
{
	setPeriod(period);
}
pg::CosineMask::CosineMask()
	:m_posX(0.0f), m_posY(0.0f)
{
	setPeriod(50.0f);
}

float pg::CosineMask::getValue(float x, float y)
{
	float dist = sqrtf((x - m_posX) * (x - m_posX) + (y - m_posY) * (y - m_posY));

	return (cosf(m_omega * dist) + 1.0f) * 0.5f;
}
