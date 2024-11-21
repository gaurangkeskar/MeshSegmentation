#pragma once
#include "Triangulation.h"
namespace Geometry {
	class RealPoint
	{
	public:
		RealPoint(double x, double y, double z);
		RealPoint(Point p, Triangulation& triangulation);
		~RealPoint();

		double X() const;
		double Y() const;
		double Z() const;

		bool operator==(RealPoint& other);
		RealPoint operator-(const RealPoint& other) const;
		RealPoint operator+(const RealPoint& other) const;
		void assign(RealPoint& other);
		RealPoint operator*(double scalar) const;

	private:
		double mX;
		double mY;
		double mZ;
	};
}


