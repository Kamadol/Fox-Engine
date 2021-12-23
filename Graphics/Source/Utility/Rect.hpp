#ifndef RECT_HPP
#define RECT_HPP

#include "Vec2.hpp"

template<typename T>
class Rect
{
public:
	Rect(Vec2<T> position, Vec2<T> quadSize, Vec2<T> totalSize);
	Rect(Vec2<T> dl, Vec2<T> ur);
	Rect();

public:
	Vec2<T> dl;
	Vec2<T> ur;

};

typedef Rect<size_t> RectUInt;
typedef Rect<int> RectInt;
typedef Rect<float> RectFloat;

template<typename T>
Rect<T>::Rect(Vec2<T> gridId, Vec2<T> quadSize, Vec2<T> totalSize)
{
	T x = totalSize.x / quadSize.x;
	T y = totalSize.y / quadSize.y;

	dl = Vec2<T>(x * gridId.x, y * gridId.y);
	ur = dl + quadSize;
}
template<typename T>
Rect<T>::Rect(Vec2<T> dl, Vec2<T> ur)
	:dl(dl), ur(ur)
{

}
template<typename T>
Rect<T>::Rect()
{

}

#endif
