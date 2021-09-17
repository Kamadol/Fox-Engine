#ifndef MIN_MASK_OPERATION
#define MIN_MASK_OPERATION

#include "MaskOperation.hpp"

namespace pg
{
	class MinMaskOperation : public MaskOperation
	{
		virtual float getValue(float v0, float v1) const
		{
			float value;

			if (v0 < v1)
				value = v0;
			else
				value = v1;

			return value;
		}
	};
}

#endif
