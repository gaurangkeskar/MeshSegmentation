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

	static double dotProduct(Point& p1, Point& p2, Triangulation& triangulation);
	static double magnitude(Point& p1, Triangulation& triangulation);
	static double getAngle(Point& n1, Point& n2, Triangulation& triangulation);

};

