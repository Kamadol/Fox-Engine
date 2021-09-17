#ifndef SUB_MASK_OPERATION_HPP
#define SUB_MASK_OPERATION_HPP

#include "MaskOperation.hpp"

namespace pg
{
	class SubMaskOperation : public MaskOperation
	{
	public:
		virtual float getValue(float v0, float v1) const
		{
			float value = v0 - v1;

			if (value <= 0.0f)
				value = 0.0f;

			return value;
		}

	};
}

#endif
