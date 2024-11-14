#pragma once
#include "Triangulation.h"

using namespace Geometry;

class RealPoint
{
	double mX;
	double mY;
	double mZ;

public:
	RealPoint(double x, double y, double z);
	~RealPoint();

	double X() const;
	double Y() const;
	double Z() const;

	bool operator==(RealPoint& other);
	RealPoint operator-(const RealPoint& other) const;
	RealPoint operator+(const RealPoint& other) const;
	void assign(RealPoint& other);
	void assign(Point& other, Triangulation& triangulation);
	RealPoint operator*(double scalar) const;
};


