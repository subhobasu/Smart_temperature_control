//#include <iostream>
#include "config.h"
#include <gtest/gtest.h>

#include "temperature_controller_module.h"

//For unit tests
#define MAX_TEMP 25.0
#define MIN_TEMP 15.0


std::string unit_test_func(double temperature)
{
	double max_temp = (double)MAX_TEMP;
	double min_temp = (double)MIN_TEMP;
	int algorithm_interval = (int)DEFAULT_ALGORITHM_INTERVAL;

	static TemperatureController temperature_controller(min_temp, max_temp, algorithm_interval);

	//temperature_controller.setMaxTemp(max_temp);
	//temperature_controller.setMinTemp(min_temp);
	//temperature_controller.setAlgorithmInterval(algorithm_interval);


	return temperature_controller.unit_test_run(temperature);
	//return "Heating";
}

TEST(testsuite_temperature_controller, Heating1) // < 15 degree Centigrade
{
	EXPECT_TRUE("Heating" == unit_test_func(12.0f));
}

TEST(testsuite_temperature_controller, Heating2) // < 15 degree Centigrade
{
	EXPECT_TRUE("Heating" == unit_test_func(-2.0f));
}

TEST(testsuite_temperature_controller, Heating3) // < 15 degree Centigrade
{
	EXPECT_FALSE("Heating" == unit_test_func(35.0f)); // Test FALSE
}

TEST(testsuite_temperature_controller, Heating4) // < 15 degree Centigrade
{
	EXPECT_TRUE("Heating" == unit_test_func(5.0f));
}


TEST(testsuite_temperature_controller, Cooling1) // > 25 degree Centigrade
{
	EXPECT_TRUE("Cooling" == unit_test_func(32.0f));
}

TEST(testsuite_temperature_controller, Cooling2) // > 25 degree Centigrade
{
	EXPECT_TRUE("Cooling" == unit_test_func(26.0f));
}

TEST(testsuite_temperature_controller, Cooling3) // > 25 degree Centigrade
{
	EXPECT_FALSE("Cooling" == unit_test_func(17.0f)); // Test FALSE
}


TEST(testsuite_temperature_controller, Neutral1) // 15 <= t <= 25 degree Centigrade
{
	EXPECT_TRUE("Neutral" == unit_test_func(15.0f));
}


TEST(testsuite_temperature_controller, Neutral2) // 15 <= t <= 25 degree Centigrade
{
	EXPECT_TRUE("Neutral" == unit_test_func(15.0f));
}

TEST(testsuite_temperature_controller, Neutral3) // 15 <= t <= 25 degree Centigrade
{
	EXPECT_TRUE("Neutral" == unit_test_func(15.0f));
}



int main_test(int argc, char **argv) {
	std::cout << "Hello World" << std::endl;
	std::cout << "Version " << Automatic_temperature_controller_VERSION_MAJOR << "." << Automatic_temperature_controller_VERSION_MINOR << std::endl;


	std::cout << "************Starting 10 static tests***************" << std::endl;
	std::cout << "Test parameters: \n";
	std::cout << "Max temperature (degree Celsius): " << MAX_TEMP << std::endl;
	std::cout << "Min temperature (degree Celsius): " << MIN_TEMP << std::endl;


	unit_test_func(0.0f);

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

	return 0;
}


