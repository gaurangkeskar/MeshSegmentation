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
        if (grouped[i]) continue;

        Triangulation currentTriangulation;
        currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
        currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);
        grouped[i] = true;

        // Get the center point of the first triangle (use average of its vertices)
        Triangle& firstTriangle = inputTriangulation.Triangles[i];
        //Point center = (firstTriangle.P1() + firstTriangle.P2() + firstTriangle.P3()) / 3.0;

        bool isSpherical = true;

        for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++) {
            if (grouped[j]) continue;

            Triangle& triangle = inputTriangulation.Triangles[j];
            //Point triangleCenter = (triangle.Vertex1 + triangle.Vertex2 + triangle.Vertex3) / 3.0;

            // Calculate the distance from the center of the first triangle
            //double distanceToCenter = (triangleCenter - center).Length();

            // Check if the triangle is approximately equidistant from the same center
            /*if (fabs(distanceToCenter) > SPHERE_TOLERANCE) {
                isSpherical = false;
                break;
            }*/

            currentTriangulation.Triangles.push_back(triangle);
            grouped[j] = true;
        }

        // If the surface contains more than one triangle and is spherical, add it
        if (isSpherical && currentTriangulation.Triangles.size() > 1) {
            sphericalSurfaces.push_back(currentTriangulation);
        }
    }
}