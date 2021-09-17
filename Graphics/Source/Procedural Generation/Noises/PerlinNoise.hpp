#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include "CoherentNoise.hpp"

namespace pg
{
	class PerlinNoise : public pg::CoherentNoise
	{
	public:
		PerlinNoise();

		virtual float getNoiseValue(float x, float y) override;

	private:
		void randomVector(int ix, int iy, float& retX, float& retY);
		float dotGridGradient(int ix, int iy, float x, float y);

	};
}

#endif
