#pragma once

#include "core.h"
#include <string>

static const double pi = 3.141592653589793;
static const double twoPi = 6.283185307179586;

struct Vector3
{
	double x;
	double y;
	double z;

	Vector3();
	Vector3(double XYZ);
	Vector3(double X, double Y, double Z);

	static double CalcLength(Vector3 v);

	static Vector3 Normalize(Vector3 v);

	static Vector3 Normalize(Vector3 v, double length);

	static Vector3 Mult(Vector3 a, Vector3 b);

	static Vector3 Scale(double s, Vector3 v);

	static Vector3 DirectionToSphericalPixel(Vector3 v, int width, int height);

	static Vector3 PixelToSphericalDirection(int pixelX, int pixelY, int width, int height);

	static std::string Vector3ToString(Vector3 v);

	friend std::ostream& operator<<(std::ostream& output, const Vector3& v);

	friend Vector3 operator* (double d, Vector3 v);

	friend Vector3 operator* (Vector3 v, double d);

	friend Vector3 operator*=(double d, Vector3 v);

	friend Vector3 operator*=(Vector3 v, double d);

	friend Vector3 operator+ (Vector3 a, Vector3 b);

	friend Vector3 operator+=(Vector3 a, Vector3 b);
};