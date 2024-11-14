#include "Utilities.h"
#include <cmath>

Utilities::Utilities()
{
}

Utilities::~Utilities()
{
}

double Utilities::dotProduct(const Point& p1, const Point& p2, const Triangulation& triangulation)
{
	
	double x = triangulation.UniqueNumbers[p1.X()] * triangulation.UniqueNumbers[p2.X()];
	double y = triangulation.UniqueNumbers[p1.Y()] * triangulation.UniqueNumbers[p2.Y()];
	double z = triangulation.UniqueNumbers[p1.Z ()] * triangulation.UniqueNumbers[p2.Z()];
	return x+y+z;
}

double Utilities::magnitude(const Point& p1, const Triangulation& triangulation)
{
	
	double x = pow(triangulation.UniqueNumbers[p1.X()], 2);
	double y = pow(triangulation.UniqueNumbers[p1.Y()], 2);
	double z = pow(triangulation.UniqueNumbers[p1.Z()], 2);

	return sqrt(x + y + z);
}

double Utilities::getAngle(const Point& n1, const Point& n2, const Triangulation& triangulation)
{
	double angle = acos(dotProduct(n1, n2, triangulation) / (magnitude(n1, triangulation) * magnitude(n2, triangulation)));
	return angle;
}
