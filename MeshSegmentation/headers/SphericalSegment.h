#pragma once
#include "Triangulation.h"
#include <vector>
using namespace Geometry;

class SphericalSegment
{
public:
	std::vector<Triangulation> curvedSurfaces;
	SphericalSegment(std::vector<Triangulation>);
	~SphericalSegment();
};
