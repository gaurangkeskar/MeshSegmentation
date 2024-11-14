#pragma once
#include "Triangulation.h"
using namespace Geometry;

class Surface
{
public:

	std::vector<Triangulation> planarSurfaces;
	std::vector<Triangulation> sphericalSurfaces;
	std::vector<Triangulation> cylindricalSurfaces;

	Surface();
	~Surface();

	void getPlanarSurfaces(Triangulation& inputTriangulation);
	void getSphericalSurfaces(Triangulation& inputTriangulation);
	void getCylindricalSurfaces(Triangulation& inputTriangulation);
};
