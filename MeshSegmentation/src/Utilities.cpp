#include "Utilities.h"
#include <cmath>

#define TOLERANCE 1e-6

Utilities::Utilities()
{
}

Utilities::~Utilities()
{
}

double Utilities::dotProduct(const RealPoint& p1, const RealPoint& p2)
{
    // Dot product formula: p1.X() * p2.X() + p1.Y() * p2.Y() + p1.Z() * p2.Z()
    double x = p1.X() * p2.X();
	double y = p1.Y() * p2.Y();
	double z = p1.Z() * p2.Z();
	return x + y + z;
}

double Utilities::magnitude(const RealPoint& p1)
{
    // Magnitude formula: sqrt(p1.X()^2 + p1.Y()^2 + p1.Z()^2)
	double x = pow(p1.X(), 2);
	double y = pow(p1.Y(), 2);
	double z = pow(p1.Z(), 2);

	return sqrt(x + y + z);
}

double Utilities::getAngle(const RealPoint& n1, const RealPoint& n2)
{
    // Cosine of the angle between two vectors: dotProduct(n1, n2) / (magnitude(n1) * magnitude(n2))
    double cosine = dotProduct(n1, n2) / (magnitude(n1) * magnitude(n2));
    // Ensure the cosine value is within the valid range [-1, 1] to avoid domain errors in acos
    cosine = std::min(1.0, std::max(-1.0, cosine));
    return acos(cosine);
	
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

    double detT = b1 * A22 - b2 * A12;
    double detS = A11 * b2 - A21 * b1;

    double t = detT / detA;
    double s = detS / detA;

    intersection = P1 + n1 * t;

    RealPoint checkPoint = P2 + n2 * s;

    if ((intersection - checkPoint).X() < TOLERANCE && (intersection - checkPoint).Y() < TOLERANCE && (intersection - checkPoint).Z() < TOLERANCE) {
        return true;
    }

    return false;
}

RealPoint Utilities::crossProduct(const RealPoint& n1, const RealPoint& n2)
{
	double x = n2.Z() * n1.Y() - n1.Z() * n2.Y();
	double y = n2.Z() * n1.X() - n1.Z() * n2.X();
	double z = n2.Y() * n1.X() - n2.X() * n1.Y();
	return RealPoint(x, -y, z);
}

void Utilities::normalize(RealPoint& p1)
{
    
    double x = p1.X() / magnitude(p1);
    double y = p1.Y() / magnitude(p1);
    double z = p1.Z() / magnitude(p1);
    RealPoint temp(x,y,z);
    p1.assign(temp);
}
