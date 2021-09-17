#ifndef MASK_OPERATION_HPP
#define MASK_OPERATION_HPP

namespace pg
{
	class MaskOperation
	{
	public:
		virtual float getValue(float v0, float next) const = 0;

	};
}

#endif
