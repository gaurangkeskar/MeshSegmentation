#pragma once
#include "Triangulation.h"
#include <unordered_map>
#include <string>

using namespace Geometry;

class Surface
{
public:

	std::vector<Triangulation> segmentedSurfaces;
	std::unordered_map<int, std::string> triangleColors;

	Surface();
	~Surface();

	void segmentTriangles(Triangulation& triangulation);

private:
	bool isCylindrical(const Point& p1, const Point& p2, const Triangulation& triangulation);
	void setColor(int triangleIndex, const std::string& color);
};