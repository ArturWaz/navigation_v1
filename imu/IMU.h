/*
 *      Author: Artur Waz
 *      Year: 2015
 */

#ifndef IMU_IMU_H_
#define IMU_IMU_H_


#include "Accelerometer.h"
#include "Gyroscope.h"


// TODO: implement


class IMU : Accelerometer, Gyroscope {
public:
	IMU();
	~IMU();
};

#endif /* IMU_IMU_H_ */
