/*
 * main.cpp
 *
 *  Created on: Dec 20, 2022
 *      Author: Administrator
 */

#include "temperature_controller_module.h"
#include "config.h"
#include <iostream>

int main_test(int argc, char **argv);
int main_deploy(int argc, char **argv);

int main(int argc, char **argv)
{
	std::cout << "Version " << Automatic_temperature_controller_VERSION_MAJOR << "." << Automatic_temperature_controller_VERSION_MINOR << std::endl;

	if(UNIT_TESTING_ENABLED)
		main_test(argc, argv);
	else
		main_deploy(argc, argv);

	return 0;
}

