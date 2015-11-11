/*
 *      Author: Artur Waz
 *      Year: 2015
 */


#include <Lidar2D.h>
#include <iostream>
#include <utility>
#include <cmath>
#include <array>
#include <cstdlib>
#include <fstream>
#include <random>

#include <boost/asio.hpp>
#include <Time.h>



#include "SimulationEnvironment.h"
#include "Point2D.h"
#include "LineSegment2D.h"
#include "RealLidar2D.h"
#include "Robot.h"



using namespace std;
using boost::asio::ip::tcp;



size_t const LENGTH = 2+2*sizeof(double);
array<uint8_t,LENGTH> packetDetectedPoint(Point2D const &p) {
	array<uint8_t,LENGTH> packet{};
	uint8_t *ptr = packet.data();
	*ptr = 0xFF;
	*(++ptr) = 0x01;
	++ptr;
	memcpy(ptr,&p.x(),sizeof(double));
	ptr += sizeof(double);
	memcpy(ptr,&p.y(),sizeof(double));
	return packet;
}





double const pi{3.1415926535897932384626433832795};
inline double rad2deg(double const &angle) { return (angle/pi)*180.; }
inline double deg2rad(double const &angle) { return (angle/180.)*pi; }




Map2D building{};
RealLidar2D lidar{&building, 5.5,s2ns(0.0005),16.38375, .00025,deg2rad(360./2340.), 0.0001,deg2rad(0.01)}; // RP lidar parameters
Robot robot;
Trajectory trajectory;


ofstream out{"out.csv",ios::out|ios::trunc};


boost::asio::io_service io_service;
tcp::socket s(io_service);
tcp::resolver resolver(io_service);


int iter{0};
nanosecond timeInterval{s2ns(0.1)};
nanosecond lastTime{0};

void lidarSimpleTest() {

	boost::asio::connect(s, resolver.resolve({"localhost", "8888"}));

	auto setup = [](SimulationEnvironment &sim) -> void {
		building.readMap("map.csv");
		trajectory.read("trajectory.csv");
		sim.setTimeSimMultiplayer(0.1);
		sim.setTimeRealEnd(s2ns(6000));
		sim.setTimeSimEnd(s2ns(57));
		sim.setTimeSimStep(s2ns(0.5e-3));
		out << "# time, x_ideal, y_ideal, x_real, y_real\n";
	};


	auto loop = [](SimulationEnvironment const &sim) -> void {
		RealLidar2D::Measure sensor{},ideal{};
		if (lidar.measure(sim.time(),robot.pose(),sensor,ideal)) {
			if (sensor.distance() < 5) {
				out << ns2s(sim.time()) << ", " << cos(ideal.angle())*ideal.distance()+robot.pose().x() << ", " <<
													sin(ideal.angle())*ideal.distance()+robot.pose().y() << ", " <<
													cos(sensor.angle())*sensor.distance()+robot.pose().x() << ", " <<
													sin(sensor.angle())*sensor.distance()+robot.pose().y() << "\n";
				array<uint8_t,LENGTH> p = packetDetectedPoint({cos(sensor.angle())*sensor.distance()+robot.pose().x(),
																sin(sensor.angle())*sensor.distance()+robot.pose().y()});
				boost::asio::write(s, boost::asio::buffer(p, p.size()));
			}
		}

		robot.moveTo(trajectory.pose(sim.time()));

		if (sim.time()%s2ns(1) == 0) cout << "Simulation time: " << ns2s(sim.time()) << "; real time: " << ns2s(sim.timeReal()) << endl;

	};



	SimulationEnvironment sim{};
	sim.setup(setup);
	sim.run(loop);


	cout << "\n\t\t FINISHED \n";
	cout << "\tSimulation time: " << ns2s(sim.time()) << "; real time: " << ns2s(sim.timeReal()) << endl;

}



int main(int argc, char *argv[]) {

	lidarSimpleTest();

//	Trajectory t;
//
//	t.read("trajectory.csv");
//	cout << t.pose(s2ns(59.51)) << endl;

}
