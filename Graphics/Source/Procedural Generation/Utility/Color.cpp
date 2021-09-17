#include "Color.hpp"

#include "Utility/Utility.hpp"

namespace pg
{
	Color Color::White = Color(255, 255, 255);
	Color Color::Black = Color(0, 0, 0);

	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		:r(r), g(g), b(b), a(a)
	{
		
	}
	//TODO
	Color::Color(uint32_t rgba)
		:r(rgba), g(rgba), b(rgba), a(rgba)
	{
		
	}
	Color::Color()
		:r(255), g(255), b(255), a(255)
	{

	}

	uint32_t Color::toUint32()
	{
		return (r << 24) + (g << 16) + (b << 8) + a;
	}

	Color Color::lerpColor(const Color& other, float w) const
	{
		uint8_t newR = (uint8_t)lerp((float)r, (float)other.r, w);
		uint8_t newG = (uint8_t)lerp((float)g, (float)other.g, w);
		uint8_t newB = (uint8_t)lerp((float)b, (float)other.b, w);
		uint8_t newA = (uint8_t)lerp((float)a, (float)other.a, w);

		return Color(newR, newG, newB, newA);
	}
	Color Color::interpolate3Color(const Color& other, float w) const
	{
		uint8_t newR = (uint8_t)interpolate3((float)r, (float)other.r, w);
		uint8_t newG = (uint8_t)interpolate3((float)g, (float)other.g, w);
		uint8_t newB = (uint8_t)interpolate3((float)b, (float)other.b, w);
		uint8_t newA = (uint8_t)interpolate3((float)a, (float)other.a, w);

		return Color(newR, newG, newB, newA);
	}
	Color Color::interpolate5Color(const Color& other, float w) const
	{
		uint8_t newR = (uint8_t)interpolate5((float)r, (float)other.r, w);
		uint8_t newG = (uint8_t)interpolate5((float)g, (float)other.g, w);
		uint8_t newB = (uint8_t)interpolate5((float)b, (float)other.b, w);
		uint8_t newA = (uint8_t)interpolate5((float)a, (float)other.a, w);

		return Color(newR, newG, newB, newA);
	}

	Color Color::operator+(const Color& c)
	{
		uint8_t newR;
		uint8_t newG;
		uint8_t newB;
		uint8_t newA;

		if ((int)r + (int)c.r > 255)
			newR = 255;
		else newR = r + c.r;

		if ((int)g + (int)c.g > 255)
			newG = 255;
		else newG = g + c.g;

		if ((int)b + (int)c.b > 255)
			newB = 255;
		else newB = b + c.b;

		if ((int)a + (int)c.a > 255)
			newA = 255;
		else newA = a + c.a;

		return Color(newR, newG, newB, newA);
	}
	Color Color::operator-(const Color& c)
	{
		uint8_t newR;
		uint8_t newG;
		uint8_t newB;
		uint8_t newA;

		if ((int)r - (int)c.r < 0)
			newR = 0;
		else newR = r - c.r;

		if ((int)g - (int)c.g < 0)
			newG = 0;
		else newG = g - c.g;

		if ((int)b - (int)c.b < 0)
			newB = 0;
		else newB = b - c.b;

		if ((int)a - (int)c.a < 0)
			newA = 0;
		else newA = a - c.a;

		return Color(newR, newG, newB, newA);
	}
	Color Color::operator*(const Color& c)
	{
		uint8_t newR = (uint8_t)((float)r * (float)c.r / 255.0f);
		uint8_t newG = (uint8_t)((float)g * (float)c.g / 255.0f);
		uint8_t newB = (uint8_t)((float)b * (float)c.b / 255.0f);
		uint8_t newA = (uint8_t)((float)a * (float)c.a / 255.0f);

		return Color(newR, newG, newB, newA);
	}

	Color& Color::operator+=(const Color& c)
	{
		if (r + c.r > 255)
			r = 255;
		else
			r += c.r;

		if (g + c.g > 255)
			g = 255;
		else
			g += c.g;

		if (b + c.b > 255)
			b = 255;
		else
			b += c.b;

		if (a + c.a > 255)
			a = 255;
		else
			a += c.a;

		return *this;
	}
	Color& Color::operator-=(const Color& c)
	{
		if (r - c.r < 0)
			r = 0;
		else
			r -= c.r;

		if (g - c.g < 0)
			g = 0;
		else
			g -= c.g;

		if (b - c.b < 0)
			b = 0;
		else
			b -= c.b;

		if (a - c.a < 0)
			a = 0;
		else
			a -= c.a;

		return *this;
	}
	Color& Color::operator*=(const Color& c)
	{
		r = (uint8_t)((float)r * float(c.r) / 255.0f);
		g = (uint8_t)((float)g * float(c.g) / 255.0f);
		b = (uint8_t)((float)b * float(c.b) / 255.0f);
		a = (uint8_t)((float)a * float(c.a) / 255.0f);

		return *this;
	}

	bool pg::Color::operator==(const Color& c)
	{
		return (r == c.r && g == c.g && b == c.b && a == c.a);
	}
	bool pg::Color::operator!=(const Color& c)
	{
		return (r != c.r || g != c.g || b != c.b || a != c.a);
	}
}
