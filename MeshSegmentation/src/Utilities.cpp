#include "Utilities.h"
#include <cmath>
#include <algorithm>

#define TOLERANCE 1e-6

Utilities::Utilities()
{
}

Utilities::~Utilities()
{
}

double Utilities::dotProduct(const RealPoint& point1, const RealPoint& point2)
{
    // Dot product formula: point1.X() * point2.X() + point1.Y() * point2.Y() + point1.Z() * point2.Z()
    double x = point1.X() * point2.X();
	double y = point1.Y() * point2.Y();
	double z = point1.Z() * point2.Z();
	return x + y + z;
}

double Utilities::magnitude(const RealPoint& point1)
{
    // Magnitude formula: sqrt(point1.X()^2 + point1.Y()^2 + point1.Z()^2)
	double x = pow(point1.X(), 2);
	double y = pow(point1.Y(), 2);
	double z = pow(point1.Z(), 2);

	return sqrt(x + y + z);
}

double Utilities::getAngle(const RealPoint& normal1, const RealPoint& normal2)
{
    // Cosine of the angle between two vectors: dotProduct(normal1, normal2) / (magnitude(normal1) * magnitude(normal2))
    double cosine = dotProduct(normal1, normal2) / (magnitude(normal1) * magnitude(normal2));
    // Ensure the cosine value is within the valid range [-1, 1] to avoid domain errors in acos
    cosine = std::min(1.0, std::max(-1.0, cosine));
    return acos(cosine);
	
}

bool Utilities::findIntersection(const RealPoint& point1, const RealPoint& normal1, const RealPoint& point2, const RealPoint& normal2,  RealPoint& intersection)
{
    // Extract direction components for the first line (normal1) and the second line (normal2)
    double A11 = normal1.X(), A12 = -normal2.X();
    double A21 = normal1.Y(), A22 = -normal2.Y();
    double A31 = normal1.Z(), A32 = -normal2.Z();

    // Compute the difference in position vectors between the two points point1 and point2
    double b1 = point2.X() - point1.X();
    double b2 = point2.Y() - point1.Y();
    double b3 = point2.Z() - point1.Z();

    // Calculate the determinant of the coefficient matrix A
    double detA;
    if((normal1.Z() - normal2.Z()) < TOLERANCE)
        detA = A11 * A22 - A12 * A21;
    else if((normal1.X() - normal2.X()) < TOLERANCE)
        detA = A31 * A22 - A32 * A21;
    else
        detA = A11 * A32 - A12 * A31;

    /*if (detA < TOLERANCE)
        return false;*/

    // Compute the determinants for t and s using the b vector and coefficient matrix A
    double detT = b1 * A22 - b2 * A12;
    double detS = A11 * b2 - A21 * b1;

    double t = detT / detA;
    double s = detS / detA;

    // Compute the intersection point by applying the parameter t to the first line (point1 + t * normal1)
    intersection = point1 + normal1 * t;

    // Compute a point on the second line using parameter s
    RealPoint checkPoint = point2 + normal2 * s;

    // Check if the two computed points (intersection and checkPoint) are close enough
    if ((intersection - checkPoint).X() < TOLERANCE && (intersection - checkPoint).Y() < TOLERANCE && (intersection - checkPoint).Z() < TOLERANCE) {
        return true;
    }

    if (magnitude(intersection - checkPoint) < TOLERANCE)
        return true;

    return false;
}

RealPoint Utilities::crossProduct(const RealPoint& normal1, const RealPoint& normal2)
{
    // Cross product formula: (normal2.Z() * normal1.Y() - normal1.Z() * normal2.Y(), normal2.Z() * normal1.X() - normal1.Z() * normal2.X(), normal2.Y() * normal1.X() - normal2.X() * normal1.Y())
	double x = normal2.Z() * normal1.Y() - normal1.Z() * normal2.Y();
	double y = normal1.Z() * normal2.X() - normal2.Z() * normal1.X();
	double z = normal2.Y() * normal1.X() - normal2.X() * normal1.Y();
	return RealPoint(x, y, z);
}

void Utilities::normalize(RealPoint& point1)
{
    // Normalize the vector by dividing each component by the magnitude   
    double x = point1.X() / magnitude(point1);
    double y = point1.Y() / magnitude(point1);
    double z = point1.Z() / magnitude(point1);
    RealPoint temp(x,y,z);
    point1 = temp;
}
