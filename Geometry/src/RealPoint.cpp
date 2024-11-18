#include "RealPoint.h"

RealPoint::RealPoint(double x, double y, double z)
	:mX(x), mY(y), mZ(z)
{
}

RealPoint::RealPoint(Point p, Triangulation& triangulation)
{
	mX = triangulation.UniqueNumbers[p.X()];
	mY = triangulation.UniqueNumbers[p.Y()];
	mZ = triangulation.UniqueNumbers[p.Z()];
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
	if (mX != other.mX || mY != other.mY || mZ != other.mZ) {
		return false;
	}
	return true;
}

RealPoint RealPoint::operator-(const RealPoint& other) const {
	return RealPoint(mX - other.mX, mY - other.mY, mZ - other.mZ);
}

RealPoint RealPoint::operator+(const RealPoint& other) const {
	return RealPoint(mX + other.mX, mY + other.mY, mZ + other.mZ);
}

void RealPoint::assign(RealPoint& other)
{
	mX = other.mX;
	mY = other.mY;
	mZ = other.mZ;
}

RealPoint RealPoint::operator*(double scalar) const {
	return RealPoint(mX * scalar, mY * scalar, mZ * scalar);
}
