/*
 * Heater.h
 *
 *  Created on: Dec 23, 2022
 *      Author: Administrator
 */

#ifndef SRC_HEATER_H_
#define SRC_HEATER_H_

//Dependency interface for temperature controller
class Heater
{
private:

	bool state_on; // On/Off
	int temp;


public:

	virtual bool isStateOn() const = 0;
	virtual void setStateOn(bool stateOn) = 0;
	virtual void setTemperature(int temp) = 0;
	virtual ~Heater() {}
	Heater() : state_on(false), temp(0) {}

};


#endif /* SRC_HEATER_H_ */
