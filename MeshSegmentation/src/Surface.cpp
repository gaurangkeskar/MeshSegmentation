#include "Surface.h"
#include "Utilities.h"
#include <unordered_set>

#define PLANAR_TOLERANCE 0.0872665
#define SPHERICAL_TOLERANCE 0.174533
#define CYLINDRICAL_TOLERANCE 0.1

Surface::Surface()
{

}

Surface::~Surface()
{

}

void Surface::segmentTriangles(Triangulation& triangulation)
{
    std::unordered_set<int> visited;
    Utilities utils;

    for (int i = 0; i < triangulation.Triangles.size(); i++) {
        if (visited.find(i) != visited.end()) continue;

        Geometry::Triangulation currentSurface;
        currentSurface.UniqueNumbers = triangulation.UniqueNumbers;

        const Point& normal1 = triangulation.Triangles[i].Normal();
        bool isPlanar = true;

        for (int j = i + 1; j < triangulation.Triangles.size(); j++) {
            if (visited.find(j) != visited.end()) continue;

            const Point& normal2 = triangulation.Triangles[j].Normal();
            double angle = utils.getAngle(normal1, normal2, triangulation);

            if (angle < PLANAR_TOLERANCE) {
                currentSurface.Triangles.push_back(triangulation.Triangles[j]);
                visited.insert(j);
                setColor(j, "red");
            }
            else if (angle < SPHERICAL_TOLERANCE) {
                bool isCylindricalSurface = isCylindrical(triangulation.Triangles[i].P1(), triangulation.Triangles[j].P1(), triangulation);

                if (isCylindricalSurface) {
                    currentSurface.Triangles.push_back(triangulation.Triangles[j]);
                    visited.insert(j);
                    setColor(j, "blue");
                }
                else {
                    currentSurface.Triangles.push_back(triangulation.Triangles[j]);
                    visited.insert(j);
                    setColor(j, "green");
                }
            }
        }

        if (currentSurface.Triangles.size() > 1) {
            segmentedSurfaces.push_back(currentSurface);
        }
    }
}

bool Surface::isCylindrical(const Point& p1, const Point& p2, const Triangulation& triangulation)
{
    double dist = sqrt(pow(triangulation.UniqueNumbers[p1.X()] - triangulation.UniqueNumbers[p2.X()], 2) +
        pow(triangulation.UniqueNumbers[p1.Y()] - triangulation.UniqueNumbers[p2.Y()], 2) +
        pow(triangulation.UniqueNumbers[p1.Z()] - triangulation.UniqueNumbers[p2.Z()], 2));
    return dist < CYLINDRICAL_TOLERANCE;
}

void Surface::setColor(int triangleIndex, const std::string& color)
{
    triangleColors[triangleIndex] = color;
}
