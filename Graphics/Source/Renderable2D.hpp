#ifndef RENDERABLE_2D_HPP
#define RENDERABLE_2D_HPP

#include <vector>

template <typename T>
class Renderable2D
{
public:
	virtual void getGeometry() const = 0;

protected:
	std::vector<T> m_vertices;

};

#endif
