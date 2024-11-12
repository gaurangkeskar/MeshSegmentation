#pragma once
#include "Point.h"
#include <vector>
using namespace Geometry;

class Utilities
{
public:
	Utilities();
	~Utilities();

	double dotProduct(Point& p1, Point& p2);
	double magnitude(Point& p1);

};

