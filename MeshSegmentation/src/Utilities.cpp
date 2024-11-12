#include "Utilities.h"
#include <cmath>

Utilities::Utilities()
{
}

Utilities::~Utilities()
{
}

double Utilities::dotProduct(Point& p1, Point& p2, Triangulation& triangulation)
{
	
	double x = triangulation.UniqueNumbers[p1.X()] * triangulation.UniqueNumbers[p2.X()];
	double y = triangulation.UniqueNumbers[p1.Y()] * triangulation.UniqueNumbers[p2.Y()];
	double z = triangulation.UniqueNumbers[p1.Z ()] * triangulation.UniqueNumbers[p2.Z()];
	return x+y+z;
}

double Utilities::magnitude(Point& p1, Triangulation& triangulation)
{
	
	double x = pow(triangulation.UniqueNumbers[p1.X()], 2);
	double y = pow(triangulation.UniqueNumbers[p1.Y()], 2);
	double z = pow(triangulation.UniqueNumbers[p1.Z()], 2);

	return sqrt(x + y + z);
}

double Utilities::getAngle(Point& n1, Point& n2, Triangulation& triangulation)
{
	double angle = acos(dotProduct(n1, n2, triangulation) / (magnitude(n1, triangulation) * magnitude(n2, triangulation)));
	return angle;
}

