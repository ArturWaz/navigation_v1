/*
 *      Author: Artur Waz
 *      Year: 2015
 */


#include <Lidar2D.h>
#include <iostream>
#include <utility>
#include <cmath>
#include <array>



#include "SimulationEnvironment.h"
#include "Timer.h"
#include "Point2D.h"
#include "LineSegment2D.h"



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


double func(double t) {
	if (t == 2) return 2.;
	return .0;
}






int main() {


	/*auto func = [](nanosecond t) -> double {
		if (t%2) return 1.;
		return .0;
	};*/


	auto setup = [](SimulationEnvironment &sim) -> void {
		sim.setTimeRealEnd(1000);
		sim.setTimeSimStep(0.1);
	};


	auto loop = [](SimulationEnvironment const &sim) -> void {

		//bool intt = generator.checkInterrupt(sim.timeSim(),func);
		//cout << "Time:   " << sim.timeSim_d() << ";   int check:   " << intt << endl;
	};



	SimulationEnvironment sim{};
	sim.setup(setup);
	//sim.run(loop);




	Map2D m{};
	Lidar2D sense{&m};

	m.lineSegments = vector<LineSegment2D>{LineSegment2D(Point2D(-2,-3),Point2D(10.112,20.007))};


	//cout << m.edge_[0].p0() << "   " << m.edge_[0].p1() << endl;
	Point2D p{7,12};
	double angle{152.2356585*sense.pi/180.};

	cout << "distance: " << sense.measure(p,angle) << endl;

	//cout << m.edge_.size() << endl;

	//cout << p[0] << "   " << p[1] << endl;
	//cout << p1[0] << "   " << p1[1] << endl;

	//cout << p.distance(p1) << endl;


	/*QuadratureGenerator generator;
	QuadratureInput sensor;

	nanosecond timeLast = 0;

	generator.setSpeed(1);

	while (true) {


		nanosecond t = WorldClock.getTime();
		if (t == 0 *1e9){
			cout << "time: " << t << endl;
			generator.setSpeed(0);
		}
		else if(t == 5 *1e9){
			cout << "time: " << t << endl;
			generator.setSpeed(1);
		}
		else if(t == 10 *1e9){
			cout << "time: " << t << endl;
			generator.setSpeed(0);
		}


		generator.run(sensor);


		nanosecond time = WorldClock.getTime();
		if ( 1 *1e9 <= time - timeLast) {


			cout << sensor.pose() << ", " << t << ", " << time << endl;


			timeLast = time;
		}

		WorldClock.nextStep(1e6); // sim step = 1ms
		usleep(500);
	}*/

}
