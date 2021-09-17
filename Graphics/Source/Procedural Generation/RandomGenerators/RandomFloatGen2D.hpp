#ifndef RANDOM_FLOAT_GEN_2D
#define RANDOM_FLOAT_GEN_2D

namespace pg
{
	class RandomFloatGen2D
	{
	public:
		RandomFloatGen2D()
			:m_seed(123456789)
		{

		}

		void setSeed(int seed) { m_seed = seed; }

		virtual float getRandomValue(int x, int y) = 0;

	protected:
		int m_seed;

	};
}

#endif
