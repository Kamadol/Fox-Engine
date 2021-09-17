#ifndef COHERENT_NOISE_HPP
#define COHERENT_NOISE_HPP

#include <memory>

#include "RandomGenerators/RandomFloatGen2D.hpp"

namespace pg
{
	class CoherentNoise
	{
	public:
		CoherentNoise();

		virtual float getNoiseValue(float x, float y) = 0;

		void setRandFloatGen2D(RandomFloatGen2D* randGen);
		void setSeed(int seed);

	protected:
		std::unique_ptr<RandomFloatGen2D> m_randGen;

	};
}

#endif
