#pragma once
#include "Triangulation.h"
#include "Segment.h"
using namespace Geometry;

class Segmenter
{
public:
	void processPlanarSurfaces(Triangulation& inputTriangulation, Segment& );
	void processSphericalSurfaces(Triangulation& inputTriangulation, Segment&);
	void processCylindricalSurfaces(Triangulation& inputTriangulation, Segment&);
};
