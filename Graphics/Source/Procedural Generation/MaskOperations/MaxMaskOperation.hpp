#ifndef MAX_MASK_OPERATION
#define MAX_MASK_OPERATION

#include "MaskOperation.hpp"

namespace pg
{
	class MaxMaskOperation : public MaskOperation
	{
		virtual float getValue(float v0, float v1) const
		{
			float value;

			if (v0 > v1)
				value = v0;
			else
				value = v1;

			return value;
		}
	};
}

#endif
