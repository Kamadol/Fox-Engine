#include "RandomIntGen.hpp"

RandomIntGen::RandomIntGen(size_t a, size_t b, size_t m)
	:m_a(a), m_b(b), m_m(m)
{
	m_lastValue = b % m;
}

size_t RandomIntGen::getRandomValue()
{
	m_lastValue = (m_a * m_lastValue + m_b) % m_m;
	return m_lastValue;
}
