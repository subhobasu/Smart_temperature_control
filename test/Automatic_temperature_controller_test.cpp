#include <temperature_controller_module.h>
#include "Heater.h"
#include <iostream>
#include "config.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Mock_Heater : public Heater //Mocked heater
{
public:

	MOCK_METHOD(bool, isStateOn, (), (const, override));
	MOCK_METHOD(void, setStateOn, (bool stateOn), (override));
	MOCK_METHOD(void, setTemperature, (int temp), (override));

	Mock_Heater() : Heater() {}
	~Mock_Heater() {}

};



//For unit tests
#define MAX_TEMP 25.0
#define MIN_TEMP 15.0


std::string unit_test_func(double temperature)
{
	double max_temp = (double)MAX_TEMP;
	double min_temp = (double)MIN_TEMP;
	int algorithm_interval = (int)DEFAULT_ALGORITHM_INTERVAL;

	static TemperatureController temperature_controller(min_temp, max_temp, algorithm_interval);

	return temperature_controller.unit_test_run(temperature);
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


//Mocks
using ::testing::AtLeast;

TEST(HeaterTestSuite, CanCallHeaterFunc) {
  Mock_Heater mock_heater;

  EXPECT_CALL(mock_heater, isStateOn)
      .Times(AtLeast(1));

  EXPECT_CALL(mock_heater, setStateOn(true)) // Turn on/off heater
        .Times(AtLeast(1));

  TemperatureController temperature_controller(15, 25, 5);

  EXPECT_FALSE(temperature_controller.getHeaterState(&mock_heater)); // Check initial heater state

  temperature_controller.getHeaterState(&mock_heater); // Check call passes
  //temperature_controller.setHeaterState(&mock_heater, true); // Check call fails
}

using ::testing::An;
using ::testing::Matcher;
using ::testing::Lt;

TEST(HeaterTestSuite, Arguments) {
  Mock_Heater mock_heater;

  EXPECT_CALL(mock_heater, isStateOn) // Should pass
      .Times(AtLeast(1));

  EXPECT_CALL(mock_heater, setStateOn(An<bool>())) // Should pass
        .Times(AtLeast(1));

  EXPECT_CALL(mock_heater, setTemperature(Matcher<int>(Lt(30)))) // Should pass
          .Times(AtLeast(1));

  TemperatureController temperature_controller(15, 25, 5);

  temperature_controller.getHeaterState(&mock_heater); // Check call passes
  temperature_controller.setHeaterState(&mock_heater, true); // Check call passes
  temperature_controller.setHeaterTemperature(&mock_heater, 35); // Check call fails
}


using ::testing::Return;

TEST(HeaterTestSuite, ReturnValues) {
  Mock_Heater mock_heater;

  EXPECT_CALL(mock_heater, isStateOn) // Should pass
      .WillOnce(Return(false))
	  .WillOnce(Return(true));

  TemperatureController temperature_controller(15, 25, 5);

  EXPECT_FALSE(temperature_controller.getHeaterState(&mock_heater)); // Check call passes
  EXPECT_FALSE(temperature_controller.getHeaterState(&mock_heater)); // Check call fails

}


int main_test(int argc, char **argv) {

	std::cout << "************Starting 13 static tests***************" << std::endl;
	std::cout << "Test parameters: \n";
	std::cout << "Max temperature (degree Celsius): " << MAX_TEMP << std::endl;
	std::cout << "Min temperature (degree Celsius): " << MIN_TEMP << std::endl;

	unit_test_func(0.0f);

	testing::InitGoogleTest(&argc, argv);
	//testing::InitGoogleMock(&argc, argv);
	RUN_ALL_TESTS();

	std::cin.get();

	return 0;

}


