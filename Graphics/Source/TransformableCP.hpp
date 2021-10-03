#ifndef TRANSFORMABLE_CP_HPP
#define TRANSFORMABLE_CP_HPP

#include <vector>

#include "Transformable.hpp"

class TransformableCP : public Transformable
{
public:
	TransformableCP();

	void addChildren(TransformableCP* other);
	size_t childrenCount() const;
	size_t childrenGlobalCount() const;

	Mat4x4 getGlobalTransform() const;

protected:
	TransformableCP* m_parent;
	std::vector<TransformableCP*> m_children;

};

#endif
