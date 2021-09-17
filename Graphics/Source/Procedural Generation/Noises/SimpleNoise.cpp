#include "SimpleNoise.hpp"

#include <cmath>

#include "Utility/Utility.hpp"

float pg::SimpleNoise::getNoiseValue(float x, float y)
{
	int x0 = (int)x;
	int x1 = x0 + 1;
	int y0 = (int)y;
	int y1 = y0 + 1;

	float v00 = sinf(m_randGen->getRandomValue(x0, y0));
	float v10 = sinf(m_randGen->getRandomValue(x1, y0));
	float v01 = sinf(m_randGen->getRandomValue(x0, y1));
	float v11 = sinf(m_randGen->getRandomValue(x1, y1));

	float wx = x - (float)x0;
	float wy = y - (float)y0;

	float vu = lerp(v00, v10, wx);
	float vd = lerp(v01, v11, wx);
	float vr = lerp(v10, v11, wy);
	float vl = lerp(v00, v01, wy);

	float ix = interpolate5(vl, vr, wx);
	float iy = interpolate5(vu, vd, wy);

	return (ix + iy) * 0.5f;
}
