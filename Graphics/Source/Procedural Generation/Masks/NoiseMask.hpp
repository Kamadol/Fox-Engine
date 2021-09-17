#ifndef NOISE_MASK_HPP
#define NOISE_MASK_HPP

#include <cstdlib>

#include "Mask.hpp"

namespace pg
{
	class NoiseMask : public Mask
	{
	public:
		virtual float getValue(float x, float y) override;

	};
}

#endif
