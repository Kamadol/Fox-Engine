#include "PerlinNoise.hpp"

#include <cmath>

#include "RandomGenerators/BasicRandomFloatGen2D.hpp"

#include "Utility/Utility.hpp"

pg::PerlinNoise::PerlinNoise()
{
	
}

float pg::PerlinNoise::getNoiseValue(float x, float y)
{
	int x0 = (int)x;
	int x1 = x0 + 1;
	int y0 = (int)y;
	int y1 = y0 + 1;

	float sx = x - (float)x0;
	float sy = y - (float)y0;

	float n0, n1, ix0, ix1, value;

	n0 = dotGridGradient(x0, y0, x, y);
	n1 = dotGridGradient(x1, y0, x, y);
	ix0 = interpolate5(n0, n1, sx);

	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	ix1 = interpolate5(n0, n1, sx);

	value = interpolate5(ix0, ix1, sy);

	return value;
}

void pg::PerlinNoise::randomVector(int ix, int iy, float& retX, float& retY)
{
	float random = m_randGen->getRandomValue(ix, iy);

	retX = cosf(random);
	retY = sinf(random);
}
float pg::PerlinNoise::dotGridGradient(int ix, int iy, float x, float y)
{
	float gradientX = 0.0f;
	float gradientY = 0.0f;
	randomVector(ix, iy, gradientX, gradientY);

	float dx = x - (float)ix;
	float dy = y - (float)iy;

	return dx * gradientX + dy * gradientY;
}
