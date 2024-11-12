#include "Utilities.h"
#include "Triangulation.h"
#include <cmath>

Utilities::Utilities()
{
}

Utilities::~Utilities()
{
}

double Utilities::dotProduct(Point& p1, Point& p2)
{
	Triangulation triangulation;
	double x = triangulation.UniqueNumbers[p1.X()] * triangulation.UniqueNumbers[p2.X()];
	double y = triangulation.UniqueNumbers[p1.Y()] * triangulation.UniqueNumbers[p2.Y()];
	double z = triangulation.UniqueNumbers[p1.Z ()] * triangulation.UniqueNumbers[p2.Z()];
	return x+y+z;
}

double Utilities::magnitude(Point& p1)
{
	Triangulation triangulation;
	double x = pow(triangulation.UniqueNumbers[p1.X()], 2);
	double y = pow(triangulation.UniqueNumbers[p1.Y()], 2);
	double z = pow(triangulation.UniqueNumbers[p1.Z()], 2);

	return sqrt(x + y + z);
}

