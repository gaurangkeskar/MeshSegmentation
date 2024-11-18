#pragma once
#include "Triangulation.h"
using namespace Geometry;

class Segment
{
public:
	std::vector<Triangulation> planarSurfaces;
	std::vector<Triangulation> sphericalSurfaces;
	std::vector<Triangulation> cylindricalSurfaces;

	Segment();
	~Segment();
};
