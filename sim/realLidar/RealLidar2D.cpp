/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#include <realLidar/RealLidar2D.h>
#include <cmath>
#include <chrono>






RealLidar2D::~RealLidar2D() {}


RealLidar2D::RealLidar2D(Map2D const *map, const double& scanSpeed, nanosecond const samplingTime, const double& rangeMax) noexcept :
			Lidar2D(map),
			scanSpeed_{scanSpeed*2.*pi},
			rangeMax_{rangeMax},
			rangeMin_{.0},
			rangeResolution_{.0},
			angleResolution_{.0},
			scanAngle_{.0},
			samplingTime_{samplingTime},
			timeLastMeasure_{-2*samplingTime},
			generator{unsigned(std::chrono::system_clock::now().time_since_epoch().count())},
			rangeDistribution{.0,.0},
			angleDistribution{.0,.0} {}


RealLidar2D::RealLidar2D(Map2D const *map, double const &scanSpeed, nanosecond const samplingTime, double const &rangeMax,
		double const &rangeResolution, double const &angleResolution,
		double const &rangeNoiseVariance, double const &angleNoiseVariance, unsigned const &seed,
		double const &rangeMin, double const &scanAngle) noexcept :
			Lidar2D(map),
			scanSpeed_{scanSpeed*2.*pi},
			rangeMax_{rangeMax},
			rangeMin_{rangeMin},
			rangeResolution_{std::abs(rangeResolution)},
			angleResolution_{std::abs(angleResolution)},
			scanAngle_{std::fmod(scanAngle,2.*pi)/2.},
			samplingTime_{samplingTime},
			timeLastMeasure_{-2*samplingTime},
			generator{seed ? seed : unsigned(std::chrono::system_clock::now().time_since_epoch().count()) },
			rangeDistribution{.0,std::sqrt(rangeNoiseVariance)},
			angleDistribution{.0,std::sqrt(angleNoiseVariance)} {}



bool RealLidar2D::measure(const nanosecond& time, const Point2D& pose, Measure &valueSensed) noexcept {
	Measure m{};
	return measure(time,pose,valueSensed,m);
}



bool RealLidar2D::measure(const nanosecond& time, const Point2D& pose, Measure &valueSensed, Measure &valueIdeal) noexcept {

	if (time - timeLastMeasure_ < samplingTime_)
		return false;

	auto applyRes = [](double const &value, double const &resolution) -> double {
		if (resolution == .0) return value;
		return resolution*int(value/resolution);
	};

	auto rangeLimit = [&](double const &value) -> double {
		if (value < rangeMin_) return rangeMin_;
		if (rangeMax_ < value) return rangeMax_;
		return value;
	};

	auto angleLimit = [&](double const &value) -> double {
		return value<.0? 2.*pi+value : std::fmod(value,2.*pi) ;
	};

	double const rangeNoise{rangeDistribution(generator)};
	double const angleNoise{angleDistribution(generator)};

	valueIdeal.m[1] = angleLimit(ns2s(time)*scanSpeed_);


	if (scanAngle_ == .0 || valueIdeal.m[1] <= scanAngle_ || 2.*pi-scanAngle_ <= valueIdeal.m[1]) {
		Lidar2D const *lidar = this;
		valueIdeal.m[0] = lidar->measure(valueIdeal.m[1],pose);
		valueSensed.m[0] = applyRes(rangeLimit(valueIdeal.m[0] + rangeNoise),rangeResolution_);
		valueSensed.m[1] = applyRes(angleLimit(valueIdeal.m[1] + angleNoise),angleResolution_);
		return true;
	}

	valueIdeal.m[0] = .0;
	valueSensed.m[0] = applyRes(rangeLimit(rangeNoise),rangeResolution_);
	valueSensed.m[1] = applyRes(angleLimit(valueIdeal.m[1] + angleNoise),angleResolution_);
	return true;
}

