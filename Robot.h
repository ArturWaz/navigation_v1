/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#ifndef ROBOT_H_
#define ROBOT_H_


#include <Time.h>
#include <fstream>
#include "Point2D.h"


class Path {
public:

	Path() noexcept {
		path_ = std::vector<Point2D>{{0.0,0.0}, {1.0,0.991791290426}, {2.0,1.97771931684}, {3.0,2.9477326419}, {4.0,3.88041209984},
			{5.0,4.72767151126}, {6.0,5.3804106122}, {7.0,5.94772872003}, {8.0,6.47771019518}, {9.0,6.99177032541},
			{10.0,7.49995216831}, {11.0,8.00809992651}, {12.0,8.52203337978}, {13.0,9.05170493663}, {14.0,9.6183085139},
			{15.0,10.2694181924}, {16.0,11.1129694121}, {17.0,12.0372130686}, {18.0,12.9880374569}, {19.0,13.9303172181},
			{20.0,14.8228235156}, {21.0,15.5887752314}, {22.0,16.2990902336}, {23.0,16.9849458507}, {24.0,17.6600484556},
			{25.0,18.3304237848}, {26.0,18.9987208699}, {27.0,19.6661043131}, {28.0,20.3330861136}, {29.0,20.9998913259},
			{30.0,21.6666189054}, {31.0,22.3333123558}, {32.0,22.9999908163}, {33.0,23.6666627499}, {34.0,24.3333318985}, {35.0,25.0}};
	}

	Point2D pose(size_t const &i) const noexcept {
		return path_[i];
	}

	size_t numberOfPoits() const noexcept { return path_.size(); }

private:

	std::vector<Point2D> path_;

};



class Trajectory {
public:

	bool read(std::string const &fileName) {
		std::ifstream in{fileName,std::iostream::in};
		if (!in.is_open()) return false;

		//std::string const message{"Cannot properly parse input map file."};

		auto parseLine = [](std::string const &str) -> TrajectoryPoint {
			TrajectoryPoint point{};
			char *ptr = const_cast<char*>(str.data());

			point.t = s2ns(strtod(ptr,&ptr));
			if (*ptr != ',') throw 3;
			point.p.x() = strtod(++ptr,&ptr);
			if (*ptr != ',') throw 5;
			point.p.y() = strtod(++ptr,&ptr);

			return point;
		};


		try {
			std::string fileLine{};
			while (std::getline(in,fileLine)) {
				if (fileLine.at(0) != '#')
					trajectory.push_back(parseLine(fileLine));
			}
		} catch (...) {
			throw std::runtime_error("Cannot properly parse input trajectory file.");
		}

		return true;
	}

	Point2D pose(nanosecond const &time) const noexcept {
		if (trajectory.empty()) return {.0,.0};

		if (time < trajectory[0].t)
			return trajectory[0].p;
		if (time > trajectory[trajectory.size()-1].t)
			return trajectory[trajectory.size()-1].p;

		size_t indP1 = find(0,trajectory.size(),time);

		double const c{double(time-trajectory[indP1].t)/double(trajectory[indP1+1].t-trajectory[indP1].t)};
		return {trajectory[indP1].p.x()+(trajectory[indP1+1].p.x()-trajectory[indP1].p.x())*c,
				trajectory[indP1].p.y()+(trajectory[indP1+1].p.y()-trajectory[indP1].p.y())*c};
	}

private:

	struct TrajectoryPoint {
		Point2D p;
		nanosecond t;
	};

	size_t find(size_t const &begin, size_t const &end, nanosecond const &t) const noexcept {
		size_t mid = (begin+end)/2;
		if (t == trajectory[mid].t) return mid;
		if (end - begin == 1) return begin;
		if (t < trajectory[mid].t) return find(begin,mid,t);
		if (t > trajectory[mid].t) return find(mid,end,t);
		return 0;
	}

	std::vector<TrajectoryPoint> trajectory;

};



class Robot {
public:

	Robot() {}

	void moveTo(Point2D const &pose) { pose_ = pose; }

	Point2D const &pose() const noexcept { return pose_; }


private:

	Point2D pose_;

};


#endif /* ROBOT_H_ */
