#ifndef SIMPLE_NOISE_HPP
#define SIMPLE_NOISE_HPP

#include "CoherentNoise.hpp"

namespace pg
{
	class SimpleNoise : public CoherentNoise
	{
	public:
		virtual float getNoiseValue(float x, float y) override;

	};
}

#endif
