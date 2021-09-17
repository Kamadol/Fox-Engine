#include "CoherentNoise.hpp"

#include "RandomGenerators/BasicRandomFloatGen2D.hpp"

namespace pg
{
	CoherentNoise::CoherentNoise()
	{
		m_randGen.reset(new BasicRandomFloatGen2D(123456789));
	}

	void CoherentNoise::setRandFloatGen2D(RandomFloatGen2D* randGen)
	{
		m_randGen.reset(randGen);
	}
	void CoherentNoise::setSeed(int seed)
	{ 
		m_randGen->setSeed(seed); 
	}
}

