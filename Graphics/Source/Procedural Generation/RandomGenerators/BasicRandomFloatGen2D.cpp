#include "BasicRandomFloatGen2D.hpp"

#include <cmath>

namespace pg
{
	BasicRandomFloatGen2D::BasicRandomFloatGen2D(int seed)
	{
		m_seed = seed;
	}

	float BasicRandomFloatGen2D::getRandomValue(int x, int y)
	{
		float ret = 2920.0f * sinf((float)x * 21942.0f + (float)y * 171324.0f + 8912.0f) * cosf((float)x * 23157.0f * (float)y * 217832.0f + 9758.0f);

		return ret;
	}
}
