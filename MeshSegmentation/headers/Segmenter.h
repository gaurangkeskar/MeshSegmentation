#pragma once
#include "Triangulation.h"
using namespace Geometry;

class Segmenter
{
public:
	std::vector<Triangulation> processPlanarSurfaces(Triangulation& inputTriangulation);
	std::vector<Triangulation> processSphericalSurfaces(Triangulation& inputTriangulation);
};
