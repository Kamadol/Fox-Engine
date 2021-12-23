#ifndef VEC2_HPP
#define VEC2_HPP

template<typename T>
class Vec2
{
public:
	Vec2(T x, T y);
	Vec2();

	Vec2<T> operator-() const;
	Vec2<T>& operator*=(float a);
	Vec2<T>& operator/=(float a);
	Vec2<T>& operator+=(const Vec2<T>& v);
	Vec2<T>& operator-=(const Vec2<T>& v);
	Vec2<T> operator+(const Vec2<T>& v) const;
	Vec2<T> operator-(const Vec2<T>& v) const;
	Vec2<T> operator*(float a) const;
	Vec2<T> operator/(float a) const;

	bool operator==(const Vec2<T>& v) const;
	bool operator!=(const Vec2<T>& v) const;

public:
	T x, y;

};

template<typename T>
Vec2<T>::Vec2(T x, T y)
	:x(x), y(y)
{

}
template<typename T>
Vec2<T>::Vec2()
{

}

template<typename T>
Vec2<T> Vec2<T>::operator-() const
{
	return Vec2<T>(-x, -y);
}
template<typename T>
Vec2<T>& Vec2<T>::operator*=(float a)
{
	x *= a;
	y *= a;

	return *this;
}
template<typename T>
Vec2<T>& Vec2<T>::operator/=(float a)
{
	x /= a;
	y /= a;

	return *this;
}
template<typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& v)
{
	x += v.x;
	y += v.y;

	return *this;
}
template<typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}
template<typename T>
Vec2<T> Vec2<T>::operator+(const Vec2<T>& v) const
{
	return Vec2<T>(x + v.x, y + v.y);
}
template<typename T>
Vec2<T> Vec2<T>::operator-(const Vec2<T>& v) const
{
	return Vec2<T>(x - v.x, y - v.y);
}
template<typename T>
Vec2<T> Vec2<T>::operator*(float a) const
{
	return Vec2<T>(x * a, y * a);
}
template<typename T>
Vec2<T> Vec2<T>::operator/(float a) const
{
	return Vec2<T>(x / a, y / a);
}

template<typename T>
bool Vec2<T>::operator==(const Vec2<T>& v) const
{
	return x == v.x && y == v.y;
}
template<typename T>
bool Vec2<T>::operator!=(const Vec2<T>& v) const
{
	return x != v.x || y != v.y;
}

typedef Vec2<size_t> Vec2u;
typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;

#endif
