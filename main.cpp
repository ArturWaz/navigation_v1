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
#include <random>



#include "SimulationEnvironment.h"
#include "Timer.h"
#include "Point2D.h"
#include "LineSegment2D.h"
#include "RealLidar2D.h"



/*
std::pair<bool,bool> moveStep(int8_t forward) {
	bool tab[4][2] = {{false,false}, {false,true}, {true,true}, {true,false}};
	static int8_t lastSense = 0;

	lastSense = (lastSense+forward)%4;
	if (lastSense < 0) lastSense = 3;

	return std::pair<bool,bool>(tab[lastSense][0],tab[lastSense][1]);
}
*/

using namespace std;


double const pi{3.1415926535897932384626433832795};
inline double rad2deg(double const &angle) { return (angle/pi)*180.; }
inline double deg2rad(double const &angle) { return (angle/180.)*pi; }




Map2D map{};
RealLidar2D lidar{&map, 15./360.,50, .1,deg2rad(1), 2,deg2rad(0.5)};



int p[10]{};


long double sumDist{0.};
long double sumAngle{0.};

double tend{10};

void simulation() {

	auto setup = [](SimulationEnvironment &sim) -> void {
		map.readMap("map.txt");
		sim.setTimeSimMultiplayer(0);
		sim.setTimeRealEnd(s2ns(60));
		sim.setTimeSimEnd(s2ns(tend));
	};


	auto loop = [](SimulationEnvironment const &sim) -> void {
		double distance{},angle{};
		RealLidar2D::Measure measure{lidar.measure(sim.time(),Point2D{.0,.0},distance,angle)};
		cout << ns2s(sim.time()) << ":  idealRange[" << distance << "];   idealAngle[" << rad2deg(angle) <<
									"]:   range[" << measure.distance() << "]:   angle[" << rad2deg(measure.angle()) << "]\n";



//		sumDist += measure.distance();
//		sumAngle += measure.angle()>lidar.pi ? measure.angle()-2.*lidar.pi : measure.angle();
//	    if ((measure.distance()>=0.0)&&(measure.distance()<10.0)) ++p[int(measure.distance())];
	};






	SimulationEnvironment sim{};
	sim.setup(setup);
	sim.run(loop);


//	cout << "av dist: " << sumDist/tend << ",   av angle: " << sumAngle/tend << endl;
//
//	  for (int i=0; i<10; ++i) {
//	    std::cout << i << "-" << (i+1) << ": ";
//	    std::cout << std::string(p[i]*100/tend,'*') << std::endl;
//	  }

}



int main(int argc, char *argv[]) {

	simulation();

}
