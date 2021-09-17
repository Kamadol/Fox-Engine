#ifndef ADD_MASK_OPERATION_HPP
#define ADD_MASK_OPERATION_HPP

#include "MaskOperation.hpp"

namespace pg
{
	class AddMaskOperation : public MaskOperation
	{
	public:
		virtual float getValue(float v0, float v1) const
		{
			float value = v0 + v1;

			if (value >= 1.0f)
				value = 1.0f;

			return value;
		}

	};
}

#endif
