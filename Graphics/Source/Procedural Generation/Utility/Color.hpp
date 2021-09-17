#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

namespace pg
{
	class Color
	{
	public:
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		Color(uint32_t rgba);
		Color();

		uint32_t toUint32();

		Color lerpColor(const Color& other, float w) const;
		Color interpolate3Color(const Color& other, float w) const;
		Color interpolate5Color(const Color& other, float w) const;

	public:
		Color operator+(const Color& c);
		Color operator-(const Color& c);
		Color operator*(const Color& c);

		Color& operator+=(const Color& c);
		Color& operator-=(const Color& c);
		Color& operator*=(const Color& c);

		bool operator==(const Color& c);
		bool operator!=(const Color& c);

	public:
		uint8_t r, g, b, a;

	public:
		static Color White;
		static Color Black;

	};
}

#endif
