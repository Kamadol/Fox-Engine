#ifndef RANDOM_INT_GENERATOR_HPP
#define RANDOM_INT_GENERATOR_HPP

class RandomIntGen
{
public:
	RandomIntGen(size_t a, size_t b, size_t m);

	size_t getRandomValue();

private:
	size_t m_a, m_b, m_m;
	size_t m_lastValue;

};

#endif
