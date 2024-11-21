#pragma once
#include "Point.h"
#include <vector>

namespace Geometry {
	class RealPoint
	{
	public:
		RealPoint(double x, double y, double z);
		RealPoint(const RealPoint& other);
		~RealPoint();

		double X() const;
		double Y() const;
		double Z() const;

		bool operator==(RealPoint& other);
		RealPoint operator-(const RealPoint& other) const;
		RealPoint operator+(const RealPoint& other) const;
		RealPoint operator*(double scalar) const;

		void convertPointToRealPoint(Point point, std::vector<double> uniqueNumbers);

	private:
		double mX;
		double mY;
		double mZ;
	};
}


