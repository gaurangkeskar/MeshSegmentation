#include "RealPoint.h"
#include "Segmenter.h"
#include "Utilities.h"

#define TOLERANCE 0.00001
#define THRESHOLD 1e-6

using namespace Geometry;

std::vector<Triangulation>* Segmenter::processPlanarSurfaces(Triangulation& inputTriangulation)
{
	std::vector<Triangulation>* planarSurfaces = new std::vector<Triangulation>();

	for (int i = 0; i < inputTriangulation.Triangles.size(); i++)
	{
		Triangulation currentTriangulation;
		RealPoint normal1(inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[i].Normal()));

		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);

		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++)
		{
			RealPoint normal2(inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[j].Normal()));

			if (fabs(Utilities::getAngle(normal1, normal2)) < TOLERANCE)
			{
				currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);
				inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + j);
				j--;
			}
		}

		if (currentTriangulation.Triangles.size() > 1)
		{
			inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + i);
			i--;
			planarSurfaces->push_back(currentTriangulation);
		}
	}
	return planarSurfaces;
}



std::vector<Triangulation>* Segmenter::processSphericalSurfaces(Triangulation& inputTriangulation)
{
    std::vector<Triangulation>* sphericalSurfaces = new std::vector<Triangulation>();

    for (int i = 0; i < inputTriangulation.Triangles.size(); i++)
    {
        bool flag = false;
        Triangulation currentTriangulation;
        RealPoint intersection(0, 0, 0);
        RealPoint point1(inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[i].P1()));
        RealPoint normal1(inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[i].Normal()));

        currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
        currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);

        for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++)
        {
            RealPoint normal2(inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[j].Normal()));
            RealPoint point2(inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[j].P1()));
            RealPoint tempIntersection(0, 0, 0);

            if (Utilities::findIntersection(point1, normal1, point2, normal2, tempIntersection))
            {
                if (!flag)
                {
                    intersection = tempIntersection;
                    flag = true;
                }

                if (Utilities::magnitude(intersection - tempIntersection) < TOLERANCE)
                {
                    currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);
                    inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + j);
                    j--;
                }
            }
        }

        if (currentTriangulation.Triangles.size() > 1)
        {
            inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + i);
            i--;
            sphericalSurfaces->push_back(currentTriangulation);
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
//		RealPoint normal1(0, 0, 0);
//		normal1 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[i].Normal());
//
//		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
//		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);
//
//		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++) {
//			
//			RealPoint normal2(0, 0, 0);
//			normal2 = inputTriangulation.convertPointToRealPoint(inputTriangulation.Triangles[j].Normal());
//
//			if (fabs(Utilities::getAngle(normal1, normal2)) > TOLERANCE) {
//
//				//Get axis via cross product
//				RealPoint axis = Utilities::crossProduct(normal1, normal2);
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
