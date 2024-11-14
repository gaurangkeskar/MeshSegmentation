#include "Surface.h"
#include "Utilities.h"
#define TOLERANCE 0.0000001

Surface::Surface()
{

}

Surface::~Surface()
{

}

void Surface::getPlanarSurfaces(Triangulation& inputTriangulation)
{
	std::vector<bool> grouped(inputTriangulation.Triangles.size(), false);
	for (int i = 0; i < inputTriangulation.Triangles.size(); i++) {
		if (grouped[i]) continue;
		Triangulation currentTriangulation;
		Point n1 = inputTriangulation.Triangles[i].Normal();
		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);
		grouped[i] = true;
		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++) {
			if (grouped[j]) {
				continue;
			}
			Point n2 = inputTriangulation.Triangles[j].Normal();
			
			if (fabs(Utilities::getAngle(n1, n2, inputTriangulation)) < TOLERANCE) {
				currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);
				grouped[j] = true;
			}
		}
		if(currentTriangulation.Triangles.size()>1)
			planarSurfaces.push_back(currentTriangulation);
	}
}

void Surface::getCylindricalSurfaces(Triangulation& inputTriangulation)
{

}

void Surface::getSphericalSurfaces(Triangulation& inputTriangulation)
{
	std::vector<bool> grouped(inputTriangulation.Triangles.size(), false);
	for (int i = 0; i < inputTriangulation.Triangles.size(); i++) {
		std::vector<double> centrePoint;
		if (grouped[i]) continue;
		Triangulation currentTriangulation;
		Point n1 = inputTriangulation.Triangles[i].Normal();
		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);
		grouped[i] = true;
		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++) {
			if (grouped[j]) {
				continue;
			}
			Point n2 = inputTriangulation.Triangles[j].Normal();
			if (fabs(Utilities::getAngle(n1, n2, inputTriangulation)) > TOLERANCE) {
				Utilities::intersection(n1, n2, inputTriangulation);
				


				currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);
				grouped[j] = true;
			}
		}
		if (currentTriangulation.Triangles.size() > 1)
			planarSurfaces.push_back(currentTriangulation);
	}
}