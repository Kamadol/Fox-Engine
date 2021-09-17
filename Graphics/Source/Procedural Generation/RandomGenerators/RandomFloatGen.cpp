#include "RandomFloatGen.hpp"

pg::RandomFloatGen::RandomFloatGen(size_t a)
	:m_a((float)a)
{

}

float pg::RandomFloatGen::getRandomValue(int x)
{
	return sinf(x * m_a);
}
