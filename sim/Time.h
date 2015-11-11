/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#ifndef SOURCE_DIRECTORY__TIMER_H_
#define SOURCE_DIRECTORY__TIMER_H_

#include <boost/timer/timer.hpp>



typedef boost::timer::nanosecond_type nanosecond;



inline double ns2s(nanosecond const &t) noexcept {
	return double(t)/1e9;
}

inline double ns2ms(nanosecond const &t) noexcept {
	return double(t)/1e6;
}

inline double ns2us(nanosecond const &t) noexcept {
	return double(t)/1e3;
}

inline nanosecond s2ns(double const &t) noexcept {
	return t*1e9;
}




class Timer: public boost::timer::cpu_timer {
public:

    inline nanosecond const &getTime() const noexcept {
        *(const_cast<boost::timer::cpu_times*>(&cpuTimes)) = elapsed();
        return cpuTimes.wall;
    }

    inline void reset() { resume(); }

private:

    boost::timer::cpu_times cpuTimes;

};



class TimerSim {
public:

	TimerSim(): simTime_(0) {}

	inline nanosecond const &getTime() const noexcept { return simTime_; }

	inline void nextStep(nanosecond const &timeInterval) { simTime_ += timeInterval; }

	inline void reset() { simTime_ = 0; }

private:

	nanosecond simTime_;

};


#endif /* SOURCE_DIRECTORY__TIMER_H_ */
