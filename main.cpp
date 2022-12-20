/*
 * main.cpp
 *
 *  Created on: Dec 20, 2022
 *      Author: Administrator
 */


#include "temperature_controller_module.h"

int main_test(int argc, char **argv);
int main_deploy(int argc, char **argv);

int main(int argc, char **argv)
{
	if(UNIT_TESTING_ENABLED)
		main_test(argc, argv);
	else
		main_deploy(argc, argv);

	return 0;
}
