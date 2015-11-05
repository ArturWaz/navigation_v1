/*
 *      Author: Artur Waz
 *      Year: 2015
 */


#include <iostream>

#include <SimulationEnvironment.h>




SimulationEnvironment::SimulationEnvironment() noexcept:
			timeSimStep_{nanosecond(1e9)},
			timeSimEnd_{nanosecond(10*1e9)},
			timeSimMultiplayer_{1},
			timeRealEnd_{nanosecond(10*1e9)} {}


SimulationEnvironment::~SimulationEnvironment() noexcept {}




void SimulationEnvironment::setup(void (*funcSetup)(SimulationEnvironment &)) {
	funcSetup(*this);
}



void SimulationEnvironment::run(void (*funcRun)(SimulationEnvironment const &)) {
	timeSimReset();
	timeRealReset();
	while (timeReal() <= timeRealEnd_ && timeSim() <= timeSimEnd_) {

		funcRun(*this);

		clockSimulation_.nextStep(timeSimStep_);
		if (timeSimMultiplayer_ != 0) {
			nanosecond const scaledSimTime = timeSim()/timeSimMultiplayer_;
			if (scaledSimTime < timeReal()) {
				if (1. < timeSimMultiplayer_)
					std::cerr << "\tWarning: Simulation multiplayer is too big.\n";
				else
					std::cerr << "\tWarning: Cannot follow real time.\n";
				continue;
			}
			while (timeReal() < scaledSimTime);
		}
	}
	clockReal_.stop();
}


