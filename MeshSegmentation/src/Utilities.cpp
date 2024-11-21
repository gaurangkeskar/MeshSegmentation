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

bool Utilities::findIntersection(const RealPoint& p1, const RealPoint& n1, const RealPoint& p2, const RealPoint& n2,  RealPoint& intersection)
{
    // Extract direction components for the first line (n1) and the second line (n2)
    double A11 = n1.X(), A12 = -n2.X();
    double A21 = n1.Y(), A22 = -n2.Y();
    double A31 = n1.Z(), A32 = -n2.Z();

    // Compute the difference in position vectors between the two points P1 and P2
    double b1 = p2.X() - p1.X();
    double b2 = p2.Y() - p1.Y();
    double b3 = p2.Z() - p1.Z();

    // Calculate the determinant of the coefficient matrix A
    double detA = A11 * A22 - A12 * A21;

    // Compute the determinants for t and s using the b vector and coefficient matrix A
    double detT = b1 * A22 - b2 * A12;
    double detS = A11 * b2 - A21 * b1;

    double t = detT / detA;
    double s = detS / detA;

    // Compute the intersection point by applying the parameter t to the first line (P1 + t * n1)
    intersection = p1 + n1 * t;

    // Compute a point on the second line using parameter s
    RealPoint checkPoint = p2 + n2 * s;

    // Check if the two computed points (intersection and checkPoint) are close enough
    if ((intersection - checkPoint).X() < TOLERANCE && (intersection - checkPoint).Y() < TOLERANCE && (intersection - checkPoint).Z() < TOLERANCE) {
        return true;
    }

    return false;
}

RealPoint Utilities::crossProduct(const RealPoint& n1, const RealPoint& n2)
{
    // Cross product formula: (n2.Z() * n1.Y() - n1.Z() * n2.Y(), n2.Z() * n1.X() - n1.Z() * n2.X(), n2.Y() * n1.X() - n2.X() * n1.Y())
	double x = n2.Z() * n1.Y() - n1.Z() * n2.Y();
	double y = n1.Z() * n2.X() - n2.Z() * n1.X();
	double z = n2.Y() * n1.X() - n2.X() * n1.Y();
	return RealPoint(x, y, z);
}

void Utilities::normalize(RealPoint& p1)
{
    // Normalize the vector by dividing each component by the magnitude   
    double x = p1.X() / magnitude(p1);
    double y = p1.Y() / magnitude(p1);
    double z = p1.Z() / magnitude(p1);
    RealPoint temp(x,y,z);
    p1.assign(temp);
}
