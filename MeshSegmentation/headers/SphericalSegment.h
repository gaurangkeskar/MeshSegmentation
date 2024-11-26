#pragma once
#include "Triangulation.h"
#include <vector>
using namespace Geometry;

class SphericalSegment
{
public:
	std::vector<Triangulation> sphericalSurfaces;
	SphericalSegment(std::vector<Triangulation> surfaces);
	~SphericalSegment();
};
