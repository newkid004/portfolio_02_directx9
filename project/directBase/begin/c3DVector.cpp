#include "c3DVector.h"
#include "kGlobalDefine.h"

c3DVector::c3DVector(NUM_REAL x, NUM_REAL y, NUM_REAL z):
	x(x), y(y), z(z)
{
	// do nothing
}

NUM_REAL c3DVector::getLength(c3DVector & input)
{
	return sqrt(
		input.x * input.x +
		input.y * input.y +
		input.z * input.z);
}

c3DVector c3DVector::getNormalize(c3DVector & input)
{
	NUM_REAL len = getLength(input);
	return c3DVector(
		input.x / len,
		input.y / len,
		input.z / len);
}


c3DVector c3DVector::operator*(NUM_REAL scalar)
{
	return c3DVector(
		x * scalar,
		y * scalar, 
		z * scalar);
}

c3DVector c3DVector::operator+(const c3DVector & input)
{
	return c3DVector(
		x + input.x, 
		y + input.y, 
		z + input.z);
}

c3DVector c3DVector::operator-(const c3DVector & input)
{
	return c3DVector(
		x - input.x, 
		y - input.y, 
		z - input.z);
}

NUM_REAL c3DVector::operator<<(const c3DVector & input)
{
	return 
		(x * input.x) +
		(y * input.y) +
		(z * input.z);
}

c3DVector c3DVector::operator>>(const c3DVector & input)
{
	return c3DVector(
		(y * input.z - z * input.y),
		(x * input.z - z * input.x),
		(y * input.x - x * input.y));
}

c3DVector c3DVector::getTransform(const c3DMatrix & input)
{

	c3DVector 
		v1(input(0, 0), input(1, 0), input(2, 0)), 
		v2(input(0, 1), input(1, 1), input(2, 1)),
		v3(input(0, 2), input(1, 2), input(2, 2));

	return c3DVector(
		*this << v1,
		*this << v2,
		*this << v3);
}