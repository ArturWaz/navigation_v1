/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#include <realLidar/RealLidar2D.h>
#include <cmath>
#include <chrono>







RealLidar2D::~RealLidar2D() {}


RealLidar2D::RealLidar2D(Map2D const *map, const double& scanSpeed, const double& rangeMax) noexcept :
			Lidar2D(map),
			scanSpeed_{scanSpeed*2.*pi},
			rangeMax_{rangeMax},
			rangeMin_{.0},
			rangeResolution_{.0},
			angleResolution_{.0},
			scanAngle_{.0},
			generator{unsigned(std::chrono::system_clock::now().time_since_epoch().count())},
			rangeDistribution{.0,.0},
			angleDistribution{.0,.0} {}


RealLidar2D::RealLidar2D(Map2D const *map, double const &scanSpeed, double const &rangeMax,
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
			generator{seed ? seed : unsigned(std::chrono::system_clock::now().time_since_epoch().count()) },
			rangeDistribution{.0,std::sqrt(rangeNoiseVariance)},
			angleDistribution{.0,std::sqrt(angleNoiseVariance)} {}



RealLidar2D::Measure RealLidar2D::measure(const nanosecond& time, const Point2D& pose) noexcept {
	double tmp1{},tmp2{};
	return measure(time,pose,tmp1,tmp2);
}



RealLidar2D::Measure RealLidar2D::measure(const nanosecond& time, const Point2D& pose, double &distanceIdeal, double &angleIdeal) noexcept {

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

	angleIdeal = angleLimit(ns2s(time)*scanSpeed_);


	if (scanAngle_ == .0 || angleIdeal <= scanAngle_ || 2.*pi-scanAngle_ <= angleIdeal) {
		Lidar2D const *lidar = this;
		distanceIdeal = lidar->measure(angleIdeal,pose);
		return Measure{applyRes(rangeLimit(distanceIdeal + rangeNoise),rangeResolution_),
						applyRes(angleLimit(angleIdeal + angleNoise),angleResolution_)};
	}

	distanceIdeal = .0;
	return Measure{applyRes(rangeLimit(rangeNoise),rangeResolution_),
					applyRes(angleLimit(angleIdeal + angleNoise),angleResolution_)};
}

