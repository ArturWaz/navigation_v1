/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#ifndef SIM_REALLIDAR_REALLIDAR2D_H_
#define SIM_REALLIDAR_REALLIDAR2D_H_


#include "Lidar2D.h"
#include "Timer.h"

#include <random>



class RealLidar2D : Lidar2D { // lidar always rotating counter-clockwise
public:

	using Lidar2D::pi;

	class Measure {
		double d;
		double a;
	public:
		explicit Measure(double const &distance, double const &angle) noexcept : d{distance}, a{angle} {}
		double const &distance() const noexcept { return d; }
		double const &angle() const noexcept { return a; }
	};


	RealLidar2D(Map2D const *map, double const &scanSpeed, double const &rangeMax) noexcept;

	RealLidar2D(Map2D const *map, double const &scanSpeed, double const &rangeMax,
				double const &rangeResolution, double const &angleResolution,
				double const &rangeNoiseVariance = .0, double const &angleNoiseVariance = .0,
				double const &rangeMin = .0, double const &scanAngle = .0) noexcept;

	~RealLidar2D();


	Measure measure(nanosecond const &time, Point2D const &pose) noexcept;

	Measure measure(nanosecond const &time, Point2D const &pose, double &distanceIdeal, double &angleIdeal) noexcept;


private:

	double scanSpeed_; // [rotate/s]
	double rangeMax_; // [m]

	double rangeMin_; // [m]
	double rangeResolution_; // [m]

	double angleResolution_; // [m]
	double scanAngle_; // [rad]

	std::default_random_engine generator;
	std::normal_distribution<double> rangeDistribution;
	std::normal_distribution<double> angleDistribution;

};




#endif /* SIM_REALLIDAR_REALLIDAR2D_H_ */
