#pragma once
#include "Point.h"
#include "Triangulation.h"
#include <vector>
using namespace Geometry;

class Utilities
{
public:
	Utilities();
	~Utilities();

	static double dotProduct(const Point& p1, const Point& p2, const Triangulation& triangulation);
	static double magnitude(const Point& p1, const Triangulation& triangulation);
	static double getAngle(const Point& n1,const Point& n2, const Triangulation& triangulation);

};

