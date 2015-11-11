/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#ifndef SIM_REALLIDAR_REALLIDAR2D_H_
#define SIM_REALLIDAR_REALLIDAR2D_H_


#include "Lidar2D.h"
#include "../Time.h"

#include <random>



class RealLidar2D : Lidar2D { // lidar always rotating counter-clockwise
public:

	using Lidar2D::pi;

	class Measure { // angle: [0,360)
		friend class RealLidar2D;
		double m[2];
	public:
		explicit Measure() noexcept {}
		explicit Measure(double const &distance, double const &angle) noexcept : m{distance,angle} {}
		double const &distance() const noexcept { return m[0]; }
		double const &angle() const noexcept { return m[1]; }
	};


	RealLidar2D(Map2D const *map, double const &scanSpeed, nanosecond const samplingTime, double const &rangeMax) noexcept;

	RealLidar2D(Map2D const *map, double const &scanSpeed, nanosecond const samplingTime, double const &rangeMax,
				double const &rangeResolution, double const &angleResolution,
				double const &rangeNoiseVariance = .0, double const &angleNoiseVariance = .0, unsigned const &seed = 0,
				double const &rangeMin = .0, double const &scanAngle = .0) noexcept;

	~RealLidar2D();


	bool measure(nanosecond const &time, Point2D const &pose, Measure &valueSensed) noexcept;

	bool measure(nanosecond const &time, Point2D const &pose, Measure &valueSensed, Measure &valueIdeal) noexcept;


private:

	double scanSpeed_; // [rps]
	double rangeMax_; // [m]

	double rangeMin_; // [m]
	double rangeResolution_; // [m]

	double angleResolution_; // [m]
	double scanAngle_; // [rad]

	nanosecond samplingTime_;

	nanosecond timeLastMeasure_;

	std::default_random_engine generator;
	std::normal_distribution<double> rangeDistribution;
	std::normal_distribution<double> angleDistribution;

};




#endif /* SIM_REALLIDAR_REALLIDAR2D_H_ */
