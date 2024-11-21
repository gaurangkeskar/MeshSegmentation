#pragma once
#include "RealPoint.h"
using namespace Geometry;

class Utilities
{
public:
	Utilities();
	~Utilities();

	static double dotProduct(const RealPoint& p1, const RealPoint& p2);
	static double magnitude(const RealPoint& p1);
	static double getAngle(const RealPoint& n1, const RealPoint& n2);
	static bool findIntersection(const RealPoint& p1, const RealPoint& n1, const RealPoint& p2, const RealPoint& n2, RealPoint& intersection);
	static RealPoint crossProduct(const RealPoint& n1, const RealPoint& n2);
	static void normalize(RealPoint& p1);
};
