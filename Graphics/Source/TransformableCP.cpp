#include "TransformableCP.hpp"

TransformableCP::TransformableCP()
	:m_parent(nullptr)
{

}

Mat4x4 TransformableCP::getGlobalTransform() const
{
	if (m_parent != nullptr)
		return m_parent->getGlobalTransform() * getTransform();
	else
		return getTransform();
}

void TransformableCP::addChildren(TransformableCP* other)
{
	other->m_parent = this;
	m_children.push_back(other);
}
size_t TransformableCP::childrenCount() const
{
	return m_children.size();
}
size_t TransformableCP::childrenGlobalCount() const
{
	size_t ret = childrenCount();

	for (size_t i = 0; i < childrenCount(); i++)
		ret += m_children[i]->childrenGlobalCount();

	return ret;
}
