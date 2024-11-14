#include "Utilities.h"
#include <cmath>

#define EPSILON 1e-6

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
	double z = triangulation.UniqueNumbers[p1.Z()] * triangulation.UniqueNumbers[p2.Z()];
	return x + y + z;
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


RealPoint Utilities::crossProduct(const Point& n1, const Point& n2, const Triangulation& triangulation)
{
	double x = triangulation.UniqueNumbers[n2.Z()] * triangulation.UniqueNumbers[n1.Y()] - triangulation.UniqueNumbers[n1.Z()] * triangulation.UniqueNumbers[n2.Y()];
	double y = triangulation.UniqueNumbers[n2.Z()] * triangulation.UniqueNumbers[n1.X()] - triangulation.UniqueNumbers[n1.Z()] * triangulation.UniqueNumbers[n2.X()];
	double z = triangulation.UniqueNumbers[n2.Y()] * triangulation.UniqueNumbers[n1.X()] - triangulation.UniqueNumbers[n2.X()] * triangulation.UniqueNumbers[n1.Y()];
	return RealPoint(x, -y, z);
}


RealPoint findIntersection(const RealPoint& P1, const RealPoint& n1, const RealPoint& P2, const RealPoint& n2) {
   
    double A11 = n1.X(), A12 = -n2.X();
    double A21 = n1.Y(), A22 = -n2.Y();
    double A31 = n1.Z(), A32 = -n2.Z();

    // Construct direction vectors
    double b1 = P2.X() - P1.X();
    double b2 = P2.Y() - P1.Y();
    double b3 = P2.Z() - P1.Z();

    double detA = A11 * A22 - A12 * A21;
    double detT = b1 * A22 - b2 * A12; 
    double detS = A11 * b2 - A21 * b1; 

    double t = detT / detA;
    double s = detS / detA;

    // Compute the intersection point using the parameter t (from the first line)
    RealPoint intersection = P1 + n1 * t;

    // Check if the intersection point lies on the second line as well (use s)
    RealPoint checkPoint = P2 + n2 * s;

    // If the two computed points are close enough, return the intersection point
    if (fabs(intersection.X() - checkPoint.X()) < EPSILON &&
        fabs(intersection.Y() - checkPoint.Y()) < EPSILON &&
        fabs(intersection.Z() - checkPoint.Z()) < EPSILON) {
        return intersection;
    }
}