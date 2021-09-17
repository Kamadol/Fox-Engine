#include "ModRandomFloatGen2D.hpp"

#include <cmath>

#include "Utility/Utility.hpp"

namespace pg
{
	ModRandomFloatGen2D::ModRandomFloatGen2D(int modX, int modY, int seed)
		:m_modX(modX), m_modY(modY)
	{
		m_seed = seed;
	}

	void ModRandomFloatGen2D::setMod(int modX, int modY)
	{
		m_modX = modX;
		m_modY = modY;
	}

	float ModRandomFloatGen2D::getRandomValue(int x, int y)
	{
		float newX = (float)modulo(x, m_modX);
		float newY = (float)modulo(y, m_modY);

		float ret = 2920.0f * sinf(newX * 21942.0f + newY * 171324.0f + 8912.0f) * cosf(newX * 23157.0f * newY * 217832.0f + 9758.0f);

		return ret;
	}
}
