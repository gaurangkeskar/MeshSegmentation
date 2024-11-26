#pragma once
#include "RealPoint.h"
using namespace Geometry;

class Utilities
{
public:
	Utilities();
	~Utilities();

	static double dotProduct(const RealPoint& point1, const RealPoint& point2);
	static double magnitude(const RealPoint& point1);
	static double getAngle(const RealPoint& normal1, const RealPoint& normal2);
	static bool findIntersection(const RealPoint& point1, const RealPoint& normal1, const RealPoint& point2, const RealPoint& normal2, RealPoint& intersection);
	static RealPoint crossProduct(const RealPoint& normal1, const RealPoint& normal2);
	static void normalize(RealPoint& point1);
};
