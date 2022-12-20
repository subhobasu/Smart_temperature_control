# Smart_temperature_control
C++ implementation of smart temperature control
-----------------------------------------------

Objective:
Ensure that the temperature in a room is always between a min and max adjustable temperature. When temp is too low, start heating, when temp is too high start cooling.

Development goals:
1. Creating a component in C++ with api(s) 
2. Creating needed test-cases using google test (stub, mock,..)
3. Code built with cmake

Working principle (in normal simulation execution mode):
1. The temperature controller module is required to be configured initially with the values asked for the minimum and maximum temperatures (in degree Centigrade), and the frequency (in seconds) of sensing the air temperature. The data for the air temperature has been simulated as a simple random number generator between a minimum and maximum values, represented by the macros AIR_TEMPERATURE_MIN and AIR_TEMPERATURE_MAX respectively in temperature_controller_module.h. A default value of the sensing interval has also been presented with the help of macro DEFAULT_ALGORITHM_INTERVAL in the same header file.

2. The controller starts running in a parallel thread, until the user interrupts its execution by re-configuring the parameters. The options are:
   a. <Enter> : Interrupt
   b. <M/m>   : Modify the parameters
   c. <Q/q>   : Stop and quit
   
3. The controller after every configured time interval, conveys the required action of the actuator (heater/cooler) to be either "Heating", "Cooling" or "Neutral" based on the instantaneous sensed temperature value. "Heating" signifies the heater is turned on, "Cooling" signifies the cooler is turned on, and "Neutral" signifies none of them are turned on.

Execution instructions:
1. Clone and build using cmake.
2. The program has two entry points, based on the value of boolean macro UNIT_TESTING_ENABLED in file temperature_controller_module.h
   a. Unit testing mode: UNIT_TESTING_ENABLED = true
      This mode is used to test the functionality of the temperature controller. The unit tests only check whether the state ("Heating", "Cooling", "Neutral") of the         controller is reflected correctly, based on the configured values and the instantaneous air temperature supplied to it.
   
   b. Normal simulated execution mode: UNIT_TESTING_ENABLED = false (pre-built exe/Automatic_temperature_controller.exe supplied in the repository)
      This simulated mode represents the execution mode which would be visible in a real working scenario. The controller senses the temperature at regular time             intervals and based on the instantaneous air temperature and the configured min/max temperature values, the action of switching on/off the heater and cooler is         determined.
      
N.B.  This is a prototype implementation only and signifies the basic structure of the module without much added features or complexities.
