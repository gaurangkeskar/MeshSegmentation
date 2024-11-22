#pragma once
#include "Triangulation.h"
#include <vector>
using namespace Geometry;

class PlanarSegment
{
public:
	std::vector<Triangulation> planarSurfaces;
	PlanarSegment(std::vector<Triangulation>);
	~PlanarSegment();
};

