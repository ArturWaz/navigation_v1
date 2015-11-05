/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#ifndef SIMULATIONENVIRONMENT_H_
#define SIMULATIONENVIRONMENT_H_


#include "Timer.h"


/*
 *  maximum simulation or real time is about 9*10^9[s] (max(int64)), about 292 years ;D
 *
 *  times are reseted while using SimulationEnvironment::run(void (*funcRun)());
 *
 */


class SimulationEnvironment {
public:

	SimulationEnvironment() noexcept;
	virtual ~SimulationEnvironment() noexcept;


	virtual void setup() {}
	virtual void run() {}


	void setup(void (*funcSetup)(SimulationEnvironment &));
	void run(void (*funcRun)(SimulationEnvironment const &));


	inline nanosecond const &time() const noexcept { return clockSimulation_.getTime(); }
	inline nanosecond const &timeSim() const noexcept { return clockSimulation_.getTime(); }

	inline nanosecond const &timeSimStep() const noexcept { return timeSimStep_; }
	inline nanosecond const &timeReal() const noexcept { return clockReal_.getTime(); }


	inline nanosecond const &getTimeSimEnd() const noexcept { return timeSimEnd_; }
	inline nanosecond const &getTimeRealEnd() const noexcept { return timeSimEnd_; }
	inline double const &getTimeSimMultiplayer() const noexcept { return timeSimMultiplayer_; }


	inline void setTimeSimStep(nanosecond const &t) noexcept { timeSimStep_ = t<0?0:t; }
	inline void setTimeSimEnd(nanosecond const &t) noexcept { timeSimEnd_ = t<0?0:t; }
	inline void setTimeRealEnd(nanosecond const &t) noexcept { timeRealEnd_ = t<0?0:t; }
	inline void setTimeSimMultiplayer(double const &x) noexcept { timeSimMultiplayer_ = x<0?0:x; }

protected:

	inline void timeRealReset() { clockReal_.reset(); }
	inline void timeSimReset() { clockSimulation_.reset(); }

private:

	Timer clockReal_;
	TimerSim clockSimulation_;

	nanosecond timeSimStep_;
	nanosecond timeSimEnd_;
	double timeSimMultiplayer_; // if ==1 real time simulation, if ==0 as fast as possible.

	nanosecond timeRealEnd_;

};


#endif /* SIMULATIONENVIRONMENT_H_ */
