/*
 *      Author: Artur Waz
 *      Year: 2015
 */


#include <Lidar2D.h>
#include <cmath>

#include <iostream>
#include <sstream>



static double const maxDistance{1e300};


Lidar2D::Lidar2D(Map2D const *map) noexcept :
			m_{map} {}


Lidar2D::~Lidar2D() {}


double Lidar2D::measure(double const &angle, Point2D const &pose) const noexcept {
	double smallestDistance{maxDistance};

	double sangle{std::sin(pi/2-angle)};
	double cangle{std::cos(pi/2-angle)};

	auto move = [](Point2D const &center, Point2D const &point) -> Point2D
			{ return {point.x()-center.x(),point.y()-center.y()}; };

	auto rotate = [&sangle,&cangle](Point2D const &p) -> Point2D
			{ return {cangle*p.x() - sangle*p.y(), sangle*p.x() + cangle*p.y()}; };


	auto distanceToLineSegment = [&](LineSegment2D const &lineIn) -> double {
		LineSegment2D line{move(pose,lineIn.p0()),move(pose,lineIn.p1())};

		if (std::abs(line.p0().x()-line.p1().y()) <= epsilon && line.p0().y()*line.p1().y() <= 0) {
			return 0.;
		}
		double m{(line.p0().y()-line.p1().y())/(line.p0().x()-line.p1().x())};
		if (std::abs(line.p0().y()-m*line.p0().x()) <= epsilon && line.p0().y()*line.p1().y() <= 0)
			return 0.;

		line.p0() = rotate(line.p0());
		line.p1() = rotate(line.p1());

		if (std::abs(line.p0().x()*line.p1().x()) <= epsilon) {
			if (line.p0().y() < 0)   return maxDistance;
			if (line.p0().y() <= line.p1().y())   return line.p0().y();
			return line.p1().y();
		}

		if (0 < line.p0().x()*line.p1().x())   return maxDistance;

		m = (line.p0().y()-line.p1().y())/(line.p0().x()-line.p1().x());
		double const distance{line.p0().y()-m*line.p0().x()};

		if (distance < 0)   return maxDistance;

		return distance;
	};


	for (auto &lptr : m_->lineSegments) {

		double distance = distanceToLineSegment(lptr);

		if (distance < smallestDistance)
			smallestDistance = distance;
	}

	return smallestDistance;
}
