#include "NoiseMask.hpp"

float pg::NoiseMask::getValue(float x, float y)
{
	return (float)(std::rand() % 1001) / 1000.0f;
}
