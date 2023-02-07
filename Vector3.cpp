#include "Vector3.h"

Vector3::Vector3() : //empty contructor, set everything to 0
	x(0), y(0), z(0)
{
}

Vector3::Vector3(double XYZ) :
	x(XYZ), y(XYZ), z(XYZ)
{
}

Vector3::Vector3(double X, double Y, double Z) : //constructor
	x(X), y(Y), z(Z)
{
}

double Vector3::CalcLength(Vector3 v)
{
	return sqrtl((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

Vector3 Vector3::Normalize(Vector3 v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;

	double length = sqrtl((x * x) + (y * y) + (z * z));

	return Vector3(x / length, y / length, z / length);
}

Vector3 Vector3::Normalize(Vector3 v, double length)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;

	return Vector3(x / length, y / length, z / length);
}

Vector3 Vector3::Mult(Vector3 a, Vector3 b)
{
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3 Vector3::Scale(double s, Vector3 v)
{
	return Vector3(s * v.x, s * v.y, s * v.z);
}

Vector3 Vector3::DirectionToSphericalPixel(Vector3 v, int width, int height)
{
	double x = v.x; //get components of vector
	double y = v.y;
	double z = v.z;

	double length = sqrtl((x * x) + (y * y) + (z * z)); //get length of vector, add absolute value if broke

	x /= length; //normalize components of the vector
	y /= length;
	z /= length;

	double phi = atan2(y, x); //[-pi, pi]
	double theta = acos(z); //get angles [0, pi]

	Vector3 output = Vector3(phi, theta, 0);

	double scaledX = (pi + phi) * width / twoPi; //map z angle to y axis, interval [-pi/2, pi/2] -> [0, height]
	double scaledY = (theta) * height / pi; //map x angle to x axis, interval [-pi  , pi  ] -> [0, width ]

	return Vector3(scaledX, scaledY, 0);
}

Vector3 Vector3::PixelToSphericalDirection(int pixelX, int pixelY, int width, int height)
{
	double inputX = (double)pixelX / (double)width; //map pixel x to 0-1, the angle along equator
	double inputY = (double)pixelY / (double)height; //map pixel y to 0-1, the angle along meridian

	double phi = inputX * twoPi; //convert to rad angle by multiplying by pi * 2
	double theta = inputY * pi; //convert to rad angle by multiplying by pi

	double x = cos(phi) * sin(theta); //convert angles to components of velocity vector
	double y = sin(phi) * sin(theta);
	double z = cos(theta);

	return Vector3(x, y, z); //return vector
}

std::string Vector3::Vector3ToString(Vector3 v)
{
	return std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z);
}

std::ostream& operator<<(std::ostream& output, const Vector3& v)
{
	// write obj to stream
	output << v.x << " " << v.y << " " << v.z;

	return output;
}

Vector3 operator*(double d, const Vector3 v)
{
	return Vector3(d * v.x, d * v.y, d * v.z);
}

Vector3 operator*(Vector3 v, double d)
{
	return Vector3(d * v.x, d * v.y, d * v.z);
}

Vector3 operator*=(double d, Vector3 v)
{
	return Vector3(d * v.x, d * v.y, d * v.z);
}

Vector3 operator*=(Vector3 v, double d)
{
	return Vector3(d * v.x, d * v.y, d * v.z);
}

Vector3 operator+(Vector3 a, Vector3 b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 operator+=(Vector3 a, Vector3 b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}