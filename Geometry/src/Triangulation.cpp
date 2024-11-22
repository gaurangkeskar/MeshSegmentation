#include "Triangulation.h"
using namespace Geometry;
Triangulation::Triangulation()
{

}

Triangulation::~Triangulation()
{

}

RealPoint Geometry::Triangulation::convertPointToRealPoint(Point point)
{
    return RealPoint(UniqueNumbers[point.X()], UniqueNumbers[point.Y()], UniqueNumbers[point.Z()]);
}
