/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#ifndef LIDAR_LIDAR2D_H_
#define LIDAR_LIDAR2D_H_


#include <Map2D.h>




class Lidar2D {
public:

	double const pi{3.1415926535897932384626433832795};
	double epsilon{1e-15};

	Lidar2D(Map2D const *map) noexcept;
	~Lidar2D();


	double measure(double const &angle, Point2D const &pose) const noexcept;


private:

	Map2D const *m_;

};


#endif /* LIDAR_LIDAR2D_H_ */
