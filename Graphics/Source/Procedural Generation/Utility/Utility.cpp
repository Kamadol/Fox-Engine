#include "Utility.hpp"

#include <cmath>

int modulo(int x, int N)
{
	return (x % N + N) % N;
}
float modulo(float x, float N)
{
	float ret = x - N * floorf(x / N);

	return ret;
}
float dot(float x1, float y1, float x2, float y2)
{
	return x1 * x2 + y1 * y2;
}
float lerp(float v0, float v1, float w)
{
	return v0 + w * (v1 - v0);
}
float interpolate3(float v0, float v1, float w)
{
	return (v1 - v0) * (3.0 - w * 2.0) * w * w + v0;
}
float interpolate5(float v0, float v1, float w)
{
	float w2 = w * w;
	float w4 = w2 * w2;
	return v0 + (6.0f * w4 * w - 15.0f * w4 + 10.0f * w2 * w) * (v1 - v0);
}
