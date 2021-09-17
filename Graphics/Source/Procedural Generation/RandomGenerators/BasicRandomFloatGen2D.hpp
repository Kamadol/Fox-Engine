#ifndef BASIC_RANDOM_FLOAT_GEN_2D
#define BASIC_RANDOM_FLOAT_GEN_2D

#include "RandomFloatGen2D.hpp"

namespace pg
{
	class BasicRandomFloatGen2D : public RandomFloatGen2D
	{
	public:
		BasicRandomFloatGen2D(int seed);

		virtual float getRandomValue(int x, int y) override;

	};
}

#endif
