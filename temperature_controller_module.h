/*
 * temperature_controller_module.h
 *
 *  Created on: Dec 19, 2022
 *      Author: Administrator
 */

#ifndef TEMPERATURE_CONTROLLER_MODULE_H_
#define TEMPERATURE_CONTROLLER_MODULE_H_

#define UNIT_TESTING_ENABLED false

#define DEFAULT_TEMPERATURE 0.0 // (degree Centigrade)
#define AIR_TEMPERATURE_MAX 50.0
#define AIR_TEMPERATURE_MIN -30.0
#define DEFAULT_ALGORITHM_INTERVAL 5 // (in secs) Time interval of sensing temperature

#include <string>

const std::string HEATING_COOLING_STATUS_VALUES[] = {"Heating", "Neutral", "Cooling"};
#define DEFAULT_HEATING_COOLING_STATUS HEATING_COOLING_STATUS_VALUES[1] // Neutral


class TemperatureSensor
{
private:
	double temperature;

	void setTemperature(double temperature);
	// Random float generator between AIR_TEMPERATURE_MAX and AIR_TEMPERATURE_MIN
	double generateRandomFloat();

public:

	void setTemperature_unit_test(double temperature);
	const TemperatureSensor& senseTemperature();
	double getTemperature() const;

	TemperatureSensor();
	~TemperatureSensor();

};

class HeatingCoolingActuator
{
private:
	std::string heating_cooling_state;

public:
	const std::string& getHeatingCoolingState() const;
	void setHeatingCoolingState(const std::string &heatingCoolingState);

	HeatingCoolingActuator();
	~HeatingCoolingActuator();

};


class TemperatureController
{
private:
	TemperatureSensor temperature_sensor;
	double max_temp;
	double min_temp;
	int algorithm_interval; // time interval (in secs) for sensing the temperature
	HeatingCoolingActuator heating_cooling_actuator;
	bool halted;

	void temperatureControlAlgorithm();

public:

	std::string unit_test_run(double temperature);
	void run();
	int getAlgorithmInterval() const;
	void setAlgorithmInterval(int algorithmInterval);
	double getMaxTemp() const;
	void setMaxTemp(double maxTemp);
	double getMinTemp() const;
	void setMinTemp(double minTemp);
	bool isHalted() const;
	void setHalted(bool halted);

	TemperatureController(double min_temp, double max_temp, int algorithm_interval);
	~TemperatureController();

};











void haltTemperatureController(TemperatureController &temperature_controller);
void resumeTemperatureController(TemperatureController &temperature_controller);



#endif /* TEMPERATURE_CONTROLLER_MODULE_H_ */
