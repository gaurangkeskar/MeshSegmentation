#include "Segmenter.h"
#include "RealPoint.h"
#include "Utilities.h"

#define TOLERANCE 0.00001
#define THRESHOLD 1e-6

using namespace Geometry;

std::vector<Triangulation> Segmenter::processPlanarSurfaces(Triangulation& inputTriangulation)
{
	std::vector<Triangulation> planarSurfaces;
	for (int i = 0; i < inputTriangulation.Triangles.size(); i++)
	{
		Triangulation currentTriangulation;

		RealPoint p1(0, 0, 0);
		p1 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[i].P1());

		RealPoint n1(0, 0, 0);
		n1 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[i].Normal());

		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]); 

		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++)
		{
			RealPoint n2(0, 0, 0);
			n2 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[j].Normal());

			// Check if the angle between the normals is very small
			if (fabs(Utilities::getAngle(n1, n2)) < TOLERANCE)
			{
				RealPoint p2(0, 0, 0);
				p2 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[j].P1());

				RealPoint v = p2 - p1;

				currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);

				//Delete from main triangulation to avoid extra processing
				inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + j);
				j--;
			}
		}

		//Check if there are more than 1 Triangles
		if (currentTriangulation.Triangles.size() > 1) 
		{
			inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + i);
			i--;
			planarSurfaces.push_back(currentTriangulation);
		}
	}
	return planarSurfaces;
}


std::vector<Triangulation> Segmenter::processSphericalSurfaces(Triangulation& inputTriangulation)
{
	std::vector<Triangulation> sphericalSurfaces;
	for (int i = 0; i < inputTriangulation.Triangles.size(); i++) {
		bool flag = false;
		Triangulation currentTriangulation;
		RealPoint intersection(0, 0, 0);
		RealPoint p1(0, 0, 0);
		p1 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[i].P1());

		RealPoint n1(0, 0, 0);
		n1 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[i].Normal());

		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);

		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++) {
			RealPoint n2(0, 0, 0);
			n2 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[j].Normal());

			if (fabs(Utilities::getAngle(n1, n2)) > TOLERANCE) {
				RealPoint p2(0, 0, 0);
				p2 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[j].P1());

				RealPoint tempIntersection(0, 0, 0);

				// Find intersection Point
				if (Utilities::findIntersection(p1, n1, p2, n2, tempIntersection)) {

					//Check for first iteration
					if (!flag) {
						intersection = tempIntersection;
						flag = true;
					}

					//Compare the intersection point
					if (intersection == tempIntersection) {
						currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);
						inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + j);
						j--;
					}
				}
			}
		}
		if (currentTriangulation.Triangles.size() > 1)
		{
			inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + i);
			i--;
			sphericalSurfaces.push_back(currentTriangulation);
		}
	}
	return sphericalSurfaces;
}







//std::vector<Triangulation> Segmenter::processCylindricalSurfaces(Triangulation& inputTriangulation)
//{
//	for (int i = 0; i < inputTriangulation.Triangles.size(); i++) {
//		bool flag = false;
//		Triangulation currentTriangulation;
//		RealPoint intersectionAxis(0, 0, 0);
//
//		RealPoint n1(0, 0, 0);
//		n1 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[i].Normal());
//
//		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
//		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);
//
//		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++) {
//			
//			RealPoint n2(0, 0, 0);
//			n2 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[j].Normal());
//
//			if (fabs(Utilities::getAngle(n1, n2)) > TOLERANCE) {
//
//				//Get axis via cross product
//				RealPoint axis = Utilities::crossProduct(n1, n2);
//
//				//Check for first iteration
//				if (!flag) {
//					intersectionAxis = axis;
//					flag = true;
//				}
//
//				if (Utilities::magnitude(Utilities::crossProduct(intersectionAxis, axis)) < THRESHOLD) {
//					currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);
//					inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + j);
//					j--;
//				}
//			}
//		}
//		if (currentTriangulation.Triangles.size() > 1) {
//			inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + i);
//			i--;
//			cylindricalSegment.cylindricalSurfaces.push_back(currentTriangulation);
//		}
//	}
//}
