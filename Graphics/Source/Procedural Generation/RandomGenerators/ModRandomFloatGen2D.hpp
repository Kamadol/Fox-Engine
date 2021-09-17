#ifndef MOD_BASIC_RANDOM_FLOAT_GEN_2D
#define MOD_BASIC_RANDOM_FLOAT_GEN_2D

#include "RandomFloatGen2D.hpp"

namespace pg
{
	class ModRandomFloatGen2D : public RandomFloatGen2D
	{
	public:
		ModRandomFloatGen2D(int modX, int modY, int seed);

		void setMod(int modX, int modY);

	private:
		virtual float getRandomValue(int x, int y) override;

	private:
		int m_modX, m_modY;

	};
}

#endif
