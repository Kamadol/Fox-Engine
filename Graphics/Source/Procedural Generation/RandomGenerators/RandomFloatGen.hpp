#ifndef RANDOM_FLOAT_GEN_HPP
#define RANDOM_FLOAT_GEN_HPP

#include <cmath>

namespace pg
{
	class RandomFloatGen
	{
	public:
		RandomFloatGen(size_t a);

		//returns between -1 and 1
		float getRandomValue(int x);

	private:
		float m_a;

	};
}

#endif
