#include "Surface.h"
#include "Utilities.h"


Surface::Surface()
{

}

Surface::~Surface()
{

}

void Surface::getPlanarSurfaces(Triangulation& inputTriangulation)
{
	std::vector<bool> grouped(inputTriangulation.Triangles.size(), false);

	for (Triangle triangle : inputTriangulation.Triangles) {
		Triangulation triangulation;
		
	}
}

void Surface::getCylindricalSurfaces(Triangulation& inputTriangulation)
{

}

void Surface::getSphericalSurfaces(Triangulation& inputTriangulation)
{

}