#include "RealPoint.h"
#include <cmath>

#define TOLERANCE 1e-6

using namespace Geometry;

RealPoint::RealPoint(double x, double y, double z)
	:mX(x), mY(y), mZ(z)
{
}

RealPoint::RealPoint(const RealPoint& other)
	:mX(other.mX), mY(other.mY), mZ(other.mX)
{
}

RealPoint::~RealPoint()
{
	
}

double RealPoint::X() const
{
	return mX;
}

double RealPoint::Y() const
{
	return mY;
}

double RealPoint::Z() const
{
	return mZ;
}

bool RealPoint::operator==(RealPoint& other)
{
	if (fabs(mX - other.mX) > TOLERANCE || fabs(mY - other.mY) > TOLERANCE || fabs(mZ - other.mZ) > TOLERANCE) 
	{
		return false;
	}
	return true;
}

RealPoint RealPoint::operator-(const RealPoint& other) const 
{
	return RealPoint(mX - other.mX, mY - other.mY, mZ - other.mZ);
}

RealPoint RealPoint::operator+(const RealPoint& other) const 
{
	return RealPoint(mX + other.mX, mY + other.mY, mZ + other.mZ);
}

RealPoint RealPoint::operator*(double scalar) const 
{
	return RealPoint(mX * scalar, mY * scalar, mZ * scalar);
}
