#pragma once
#include "Point.h"
#include "RealPoint.h"
#include "Triangulation.h"
#include <vector>
using namespace Geometry;

class Utilities
{
public:
	Utilities();
	~Utilities();

	static double dotProduct(const RealPoint& p1, const RealPoint& p2);
	static double magnitude(const RealPoint& p1);
	static double getAngle(const RealPoint& n1, const RealPoint& n2);
	static RealPoint findIntersection(const RealPoint& P1, const RealPoint& n1, const RealPoint& P2, const RealPoint& n2);
	static RealPoint crossProduct(const Point& n1, const Point& n2, const Triangulation& triangulation);
};
