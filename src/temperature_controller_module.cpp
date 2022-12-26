/*
 * temperature_controller_module.cpp
 *
 *  Created on: Dec 19, 2022
 *      Author: Administrator
 */


#include "temperature_controller_module.h"

#include <iostream>
#include <random>
#include <windows.h>
#include <cctype>
#include <thread>


void TemperatureSensor::setTemperature(double temperature)
	{
		this->temperature = temperature;
	}


// Random float generator between AIR_TEMPERATURE_MAX and AIR_TEMPERATURE_MIN
double TemperatureSensor::generateRandomFloat()
{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dist(AIR_TEMPERATURE_MIN, AIR_TEMPERATURE_MAX);

		return dist(gen);
}

void TemperatureSensor::setTemperature_unit_test(double temperature)
{
	this->temperature = temperature;
}

const TemperatureSensor& TemperatureSensor::senseTemperature()
{
	setTemperature(generateRandomFloat());
	return *this;
}

double TemperatureSensor::getTemperature() const
{
	return temperature;
}

TemperatureSensor::TemperatureSensor() : temperature(DEFAULT_TEMPERATURE) {}
TemperatureSensor::~TemperatureSensor() {}


const std::string& HeatingCoolingActuator::getHeatingCoolingState() const {
	return heating_cooling_state;
}

void HeatingCoolingActuator::setHeatingCoolingState(const std::string &heatingCoolingState) {
	heating_cooling_state = heatingCoolingState;
}

HeatingCoolingActuator::HeatingCoolingActuator() : heating_cooling_state(DEFAULT_HEATING_COOLING_STATUS) {}
HeatingCoolingActuator::~HeatingCoolingActuator() {}


std::string TemperatureController::unit_test_run(double temperature)
{
	this->temperature_sensor.setTemperature_unit_test(temperature);
	this->temperatureControlAlgorithm();
	return this->heating_cooling_actuator.getHeatingCoolingState();
}

void TemperatureController::run()
{
	// run the temperature control algorithm, with an interval of algorithm_interval secs
	while(!halted)
	{
		this->temperature_sensor.senseTemperature();
		temperatureControlAlgorithm();
		Sleep(algorithm_interval * 1000); // in msec
	}

}

int TemperatureController::getAlgorithmInterval() const
{
	return algorithm_interval;
}

void TemperatureController::setAlgorithmInterval(int algorithmInterval)
{
	algorithm_interval = algorithmInterval;
}

double TemperatureController::getMaxTemp() const
{
	return max_temp;
}

void TemperatureController::setMaxTemp(double maxTemp)
{
	max_temp = maxTemp;
}

double TemperatureController::getMinTemp() const
{
	return min_temp;
}

void TemperatureController::setMinTemp(double minTemp)
{
	min_temp = minTemp;
}

bool TemperatureController::isHalted() const
{
	return halted;
}

void TemperatureController::setHalted(bool halted)
{
	this->halted = halted;
}

TemperatureController::TemperatureController(double min_temp, double max_temp, int algorithm_interval) :
							min_temp(min_temp),
							max_temp(max_temp),
							algorithm_interval(algorithm_interval),
							halted(true) {}



TemperatureController::~TemperatureController() {}


/* Temperature control algorithm
 * ----------------------------
 *
 * 1. Sense the air temperature (temp)
 *
 * 2. Set the actuator state with the index from HEATING_COOLING_STATUS_VALUES as below:
 *
 *		temp < min_temp               : "Heating", index 0
 *    	min_temp  <= temp <= max_temp : "Neutral", index 1
 *    	temp > max_temp				  : "Cooling", index 2
 *
 ************************************************/

void TemperatureController::temperatureControlAlgorithm()
{
	//double current_temp = temperature_sensor.senseTemperature().getTemperature();
	double current_temp = this->temperature_sensor.getTemperature();

	if (current_temp < min_temp)
		heating_cooling_actuator.setHeatingCoolingState(HEATING_COOLING_STATUS_VALUES[0]);
	else if(current_temp >= min_temp && current_temp <= max_temp)
		heating_cooling_actuator.setHeatingCoolingState(HEATING_COOLING_STATUS_VALUES[1]);
	else
		heating_cooling_actuator.setHeatingCoolingState(HEATING_COOLING_STATUS_VALUES[2]);

	if(!UNIT_TESTING_ENABLED)
	{
		std::cout << "Current temperature (degree Centigrade): " << current_temp
			   << ", actuator state: " << heating_cooling_actuator.getHeatingCoolingState()
			   << std::endl;
	}
}


bool TemperatureController::getHeaterState(Heater *heater)
{
	return heater->isStateOn();
}

void TemperatureController::setHeaterState(Heater *heater, bool stateOn)
{
	heater->setStateOn(stateOn);
}

void TemperatureController::setHeaterTemperature(Heater *heater, int temp)
{
	heater->setTemperature(temp);
}

void displayHelp()
{
	std::cout << "Temperature controller input menu" << std::endl;
	std::cout << "---------------------------------" << std::endl << std::endl;

	std::cout << "<Enter>: Pause application / Show this help screen" << std::endl;
	std::cout << "<Q/q>  : Quit the application" << std::endl;
	std::cout << "<M/m>  : Enter/modify parameters (max temp, min temp, sensing interval)" << std::endl;
}


void getUserInput(TemperatureController &temperature_controller, char &char_input, double &max_temp, double &min_temp, int &algorithm_interval)
{
	displayHelp();

	while(true) // get a valid input
	{
		//std::cin >> char_input;
		std::cin.get(char_input);
		if(char_input != '\n')
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (char_input != '\n' && toupper(char_input) != 'Q' && toupper(char_input) != 'M')
		{
			std::cout << "Invalid input, try again" << std::endl;
		}
		else
		{
			if(!temperature_controller.isHalted())
			{
				haltTemperatureController(temperature_controller);
				if (toupper(char_input) != 'Q')
					displayHelp();
			}

			if (char_input == '\n')
				continue;
			else if (toupper(char_input) == 'Q')
				return;
			else if (toupper(char_input) == 'M')
				break;
		}
	}

	//User input to set the temperature controller
	std::cout << "Max room temperature (degree Centigrade): ";
	std::cin >> max_temp;

	std::cout << "Min room temperature (degree Centigrade): ";
	std::cin >> min_temp;

	std::cout << "Time interval (in secs) of temperature sensing: ";
	std::cin >> algorithm_interval;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	return;
}

void haltTemperatureController(TemperatureController &temperature_controller)
{
	temperature_controller.setHalted(true);
	std::cout << "Temperature controller halted/non-running\n" << std::endl;

	return;
}

void resumeTemperatureController(TemperatureController &temperature_controller)
{
	temperature_controller.setHalted(false);
	std::cout << "Temperature controller resumed/running\n" << std::endl;

	return;
}

void threadRun(TemperatureController &temperature_controller)
{
	temperature_controller.run();

	return;
}

int main_deploy(int argc, char **argv) {

	double max_temp = AIR_TEMPERATURE_MAX;
	double min_temp = AIR_TEMPERATURE_MIN;
	int algorithm_interval = DEFAULT_ALGORITHM_INTERVAL;
	char char_input;

	TemperatureController temperature_controller(min_temp, max_temp, algorithm_interval);
	std::thread running_thread;

	while (true)
	{
		getUserInput(temperature_controller, char_input, max_temp, min_temp, algorithm_interval);

		if (running_thread.joinable()) // Make sure to pause the child thread if running
			running_thread.join();

		if(toupper(char_input) == 'Q')
		{
			break;
		}
		else if (toupper(char_input) == 'M')
		{
			temperature_controller.setAlgorithmInterval(algorithm_interval);
			temperature_controller.setMaxTemp(max_temp);
			temperature_controller.setMinTemp(min_temp);

			resumeTemperatureController(temperature_controller);
			running_thread = std::thread(threadRun, std::ref(temperature_controller));
		}

	}

	return 0;
}


