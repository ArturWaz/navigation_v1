/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#ifndef LINESEGMENT2D_H_
#define LINESEGMENT2D_H_


#include "Point2D.h"



class LineSegment2D: public std::array<Point2D,2> {
public:

	LineSegment2D() noexcept {}
	LineSegment2D(Point2D const &p0, Point2D const &p1) noexcept : array({p0,p1}) {}
	~LineSegment2D() {}


	inline Point2D &p0() noexcept { return *data(); }
	inline Point2D const &p0() const noexcept { return *data(); }


	inline Point2D &p1() noexcept { return *(data()+1); }
	inline Point2D const &p1() const noexcept { return *(data()+1); }


	inline double length() const noexcept { return p0().distance(p1()); }

/*
	double distance(Point2D const &p) const noexcept {
		Point2D p1_tmp(p1().x()-p0().x(),p1().y()-p1().y());
		Point2D p_tmp(p.x()-p0().x(),p.y()-p1().y());

		double angle = std::atan2(p1_tmp.y(),p1_tmp.x());
		Point2D p_tmp1(std::cos(angle)*p_tmp.x()-std::sin(angle)*p_tmp.y(), std::sin(angle)*p_tmp.x()+std::cos(angle)*p_tmp.y());

		double d[] = {p0().distance(p),p1().distance(p)};
		return 0.0;
	}
	*/

};


#endif /* LINESEGMENT2D_H_ */
