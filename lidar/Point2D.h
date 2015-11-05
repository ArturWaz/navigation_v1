/*
 *      Author: Artur Waz
 *      Year: 2015
 */


#ifndef POINT2D_H_
#define POINT2D_H_


#include <array>
#include <cmath>
#include <ostream>



class Point2D: public std::array<double,2> {
public:


	Point2D() noexcept : array({0,0}) {}
	Point2D(double const &x0, double const &x1) noexcept : array({x0,x1}) {}
	~Point2D() noexcept {}


	inline double &x() noexcept { return *(data()); }
	inline double const &x() const noexcept { return *(data()); }


	inline double &y() noexcept { return *(data()+1); }
	inline double const &y() const noexcept { return *(data()+1); }


	inline double distance(Point2D const &p) const noexcept {
		return std::sqrt((x()-p.x())*(x()-p.x()) + (y()-p.y())*(y()-p.y()));
	}

};


inline std::ostream &operator <<(std::ostream &os, Point2D const &p) {
	return os << "(" << p.x() << "," << p.y() << ")";
}


#endif /* POINT2D_H_ */
