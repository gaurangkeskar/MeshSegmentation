#include "Utilities.h"
#include <cmath>

#define EPSILON 1e-6

Utilities::Utilities()
{
}

Utilities::~Utilities()
{
}

double Utilities::dotProduct(const RealPoint& p1, const RealPoint& p2)
{

    double x = p1.X() * p2.X();
	double y = p1.Y() * p2.Y();
	double z = p1.Z() * p2.Z();
	return x + y + z;
}

double Utilities::magnitude(const RealPoint& p1)
{

	double x = pow(p1.X(), 2);
	double y = pow(p1.Y(), 2);
	double z = pow(p1.Z(), 2);

	return sqrt(x + y + z);
}

double Utilities::getAngle(const RealPoint& n1, const RealPoint& n2)
{
    double cosine = dotProduct(n1, n2) / (magnitude(n1) * magnitude(n2));
    cosine = std::min(1.0, std::max(-1.0, cosine));
    double angle = acos(cosine);
	return angle;
}

bool Utilities::findIntersection(RealPoint& P1, RealPoint& n1, RealPoint& P2, RealPoint& n2,  RealPoint& intersection)
{
    double A11 = n1.X(), A12 = -n2.X();
    double A21 = n1.Y(), A22 = -n2.Y();
    double A31 = n1.Z(), A32 = -n2.Z();

    double b1 = P2.X() - P1.X();
    double b2 = P2.Y() - P1.Y();
    double b3 = P2.Z() - P1.Z();

    double detA = A11 * A22 - A12 * A21;

    if (fabs(detA) < EPSILON) {
        if (fabs(b1 * A22 - b2 * A12) > EPSILON || fabs(A11 * b2 - A21 * b1) > EPSILON) {
            return false;
        }
        intersection.assign(P1);
        return true;
    }

    double detT = b1 * A22 - b2 * A12;
    double detS = A11 * b2 - A21 * b1;

    double t = detT / detA;
    double s = detS / detA;

    intersection = P1 + n1 * t;

    RealPoint checkPoint = P2 + n2 * s;

    if ((intersection - checkPoint).X() < EPSILON && (intersection - checkPoint).Y() < EPSILON && (intersection - checkPoint).Z() < EPSILON) {
        return true;
    }

    return false;
}

RealPoint Utilities::crossProduct(const Point& n1, const Point& n2, const Triangulation& triangulation)
{
	double x = triangulation.UniqueNumbers[n2.Z()] * triangulation.UniqueNumbers[n1.Y()] - triangulation.UniqueNumbers[n1.Z()] * triangulation.UniqueNumbers[n2.Y()];
	double y = triangulation.UniqueNumbers[n2.Z()] * triangulation.UniqueNumbers[n1.X()] - triangulation.UniqueNumbers[n1.Z()] * triangulation.UniqueNumbers[n2.X()];
	double z = triangulation.UniqueNumbers[n2.Y()] * triangulation.UniqueNumbers[n1.X()] - triangulation.UniqueNumbers[n2.X()] * triangulation.UniqueNumbers[n1.Y()];
	return RealPoint(x, -y, z);
}