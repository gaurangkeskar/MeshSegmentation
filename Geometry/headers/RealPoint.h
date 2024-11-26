#pragma once

namespace Geometry 
{
	class RealPoint
	{
	public:
		RealPoint(double x, double y, double z);
		RealPoint(const RealPoint& other);
		~RealPoint();

		double X() const;
		double Y() const;
		double Z() const;

		bool operator==(const RealPoint& other);
		RealPoint operator-(const RealPoint& other) const;
		RealPoint operator+(const RealPoint& other) const;
		RealPoint operator*(const double scalar) const;

	private:
		double mX;
		double mY;
		double mZ;
	};
}


