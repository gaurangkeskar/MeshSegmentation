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

	double dotProduct(Point& p1, Point& p2, Triangulation& triangulation);
	double magnitude(Point& p1, Triangulation& triangulation);
	double getAngle(Point& n1, Point& n2, Triangulation& triangulation);


};

