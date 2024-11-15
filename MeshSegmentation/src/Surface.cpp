#include "Surface.h"
#include "Utilities.h"
#include "RealPoint.h"
#define TOLERANCE 0.00001
#define THRESHOLD 1e-6

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
		const RealPoint n1(inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().X()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().Y()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().Z()]);
		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);
		//inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + i);
		grouped[i] = true;
		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++) {
			if (grouped[j]) {
				continue;
			}
			const RealPoint n2(inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().X()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().Y()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().Z()]);
			
			if (fabs(Utilities::getAngle(n1, n2)) < TOLERANCE) {
				currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);
				//inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + j);
				grouped[j] = true;
			}
		}
		if (currentTriangulation.Triangles.size() > 1) {
			planarSurfaces.push_back(currentTriangulation);
		}
		/*else {
			inputTriangulation.Triangles.push_back(planarSurfaces[0].Triangles[0]);
		}*/
	}
}

//void Surface::getPlanarSurfaces(Triangulation& inputTriangulation)
//{
//	for (int i = 0; i < inputTriangulation.Triangles.size(); i++) {
//		Triangulation currentTriangulation;
//		const RealPoint n1(inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().X()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().Y()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().Z()]);
//		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
//		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);
//		inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + i);
//		i--;
//		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++) {
//			const RealPoint n2(inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().X()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().Y()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().Z()]);
//			
//			if (fabs(Utilities::getAngle(n1, n2)) < TOLERANCE) {
//				currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);
//				inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + j);
//				j--;
//			}
//		}
//		if (currentTriangulation.Triangles.size() > 1) {
//			planarSurfaces.push_back(currentTriangulation);
//		}
//		else {
//			inputTriangulation.Triangles.push_back(currentTriangulation.Triangles[0]);
//			i++;
//		}
//	}
//}

void Surface::getCylindricalSurfaces(Triangulation& inputTriangulation)
{
	for (int i = 0; i < inputTriangulation.Triangles.size(); i++) {
		bool flag = false;
		Triangulation currentTriangulation;
		RealPoint intersectionAxis(0, 0, 0);

		RealPoint n1(inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().X()],
			inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().Y()],
			inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().Z()]);

		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);
		inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + i);
		i--;

		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++) {
			RealPoint n2(inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().X()],
				inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().Y()],
				inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().Z()]);

			if (fabs(Utilities::getAngle(n1, n2)) > TOLERANCE) {
				RealPoint axis = Utilities::crossProduct(n1, n2);

				if (!flag) {
					intersectionAxis.assign(axis);
					flag = true;
				}

				if (Utilities::magnitude(Utilities::crossProduct(intersectionAxis, axis)) < THRESHOLD) {
					currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);
					inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + j);
					j--;
				}
			}
		}
		if (currentTriangulation.Triangles.size() > 1)
			cylindricalSurfaces.push_back(currentTriangulation);
		else {
			inputTriangulation.Triangles.push_back(currentTriangulation.Triangles[0]);
			i++;
		}
	}
}
	


void Surface::getSphericalSurfaces(Triangulation& inputTriangulation)
{
	for (int i = 0; i < inputTriangulation.Triangles.size(); i++) {
		bool flag = false;
		Triangulation currentTriangulation;
		RealPoint intersection(0, 0, 0);
		RealPoint p1(inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].P1().X()], 
					inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].P1().Y()], 
					inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].P1().Z()]);
		RealPoint n1(inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().X()], 
			inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().Y()], 
			inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[i].Normal().Z()]);
		currentTriangulation.UniqueNumbers = inputTriangulation.UniqueNumbers;
		currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[i]);
		inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + i);
		i--;
		for (int j = i + 1; j < inputTriangulation.Triangles.size(); j++) {
			RealPoint n2(inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().X()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().Y()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].Normal().Z()]);
			if (fabs(Utilities::getAngle(n1, n2)) > TOLERANCE) {
				RealPoint p2(inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].P1().X()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].P1().Y()], inputTriangulation.UniqueNumbers[inputTriangulation.Triangles[j].P1().Z()]);

				RealPoint tempIntersection(0, 0, 0);
				if (Utilities::findIntersection(p1, n1, p2, n2, tempIntersection)) {
					if (!flag) {
						intersection.assign(tempIntersection);
						flag = true;
					}
					if (intersection == tempIntersection) {
						currentTriangulation.Triangles.push_back(inputTriangulation.Triangles[j]);
						inputTriangulation.Triangles.erase(inputTriangulation.Triangles.begin() + j);
						j--;
					}
				}
			}
		}
		if (currentTriangulation.Triangles.size() > 1)
			sphericalSurfaces.push_back(currentTriangulation);
		else {
			inputTriangulation.Triangles.push_back(currentTriangulation.Triangles[0]);
			i++;
		}

	}
}