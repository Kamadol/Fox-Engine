#ifndef CIRCULAR_ARRAY_2D_HPP
#define CIRCULAR_ARRAY_2D_HPP

#include <iostream>

#include "Utility.hpp"

template <typename T>
class CircularArray2D
{
public:
	CircularArray2D(size_t xSize, size_t ySize);

	size_t getSizeX() const { return xSize; }
	size_t getSizeY() const { return ySize; }

	T& operator()(int x, int y);

private:
	size_t xSize;
	size_t ySize;
	T** array;

};

template <typename T>
CircularArray2D<T>::CircularArray2D(size_t xSize, size_t ySize)
	:xSize(xSize), ySize(ySize)
{
	array = new T*[ySize];
	for (size_t i = 0; i < ySize; i++)
	{
		array[i] = new T[xSize];
	}
}

template <typename T>
T& CircularArray2D<T>::operator()(int x, int y)
{
	return array[modulo(y, ySize)][modulo(x, xSize)];
}

#endif
