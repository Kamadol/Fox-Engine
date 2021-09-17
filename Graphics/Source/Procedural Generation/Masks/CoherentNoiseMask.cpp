#include "CoherentNoiseMask.hpp"

#include <cmath>

#include "Noises/PerlinNoise.hpp"

namespace pg
{
	CoherentNoiseMask::CoherentNoiseMask()
		:m_posX(0.0f), m_posY(0.0f), m_startZoom(32.0f), m_octaves(6)
	{
		m_noise.reset(new PerlinNoise);
	}

	float CoherentNoiseMask::getValue(float x, float y)
	{
		float ret = 0.0f;

		float divide = 0.0f;

		for (size_t o = 0; o < m_octaves; o++)
		{
			float power = powf(0.5f, (float)o);

			float posX = (x + m_posX) / (m_startZoom * power);
			float posY = (y + m_posY) / (m_startZoom * power);

			ret += power * m_noise->getNoiseValue(posX, posY);
			divide += power;
		}

		ret /= divide;
		ret = (ret + 1.0f) * 0.5f;

		return ret;
	}

	void CoherentNoiseMask::setNoise(CoherentNoise* noise)
	{
		m_noise.reset(noise);
	}
	void CoherentNoiseMask::setSeed(int seed)
	{
		m_noise->setSeed(seed);
	}

	void CoherentNoiseMask::setXPosition(float positionX)
	{
		m_posX = positionX;
	}
	void CoherentNoiseMask::setYPosition(float positionY)
	{
		m_posY = positionY;
	}
	void CoherentNoiseMask::setStartZoom(float startZoom)
	{
		m_startZoom = startZoom;
	}
	void CoherentNoiseMask::setOctaveCount(size_t octaves)
	{
		m_octaves = octaves;
	}
}
