#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "Vector2.hpp"
#include "Vector3.hpp"

Vector2 rotate(Vector2 v, float angle);
Vector2 cubicBezier2D(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);
Vector2 cubicBezierDeriv2D(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);
Vector2 cubicBezierDDeriv2D(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);
Vector3 cubicBezier3D(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, float t);

#endif
