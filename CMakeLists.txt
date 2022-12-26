cmake_minimum_required(VERSION 3.10)

# Set some basic project attributes
project(Automatic_temperature_controller
	VERSION 0.1
	DESCRIPTION "An automatic temperature controller with google unit test project")

   
#Add sub-directories
add_subdirectory(src)
add_subdirectory(googletest)


#Add include directories
set(GMOCK_DIR "./googletest/googlemock")
set(GTEST_DIR "./googletest/googletest")
include_directories(SYSTEM ${GMOCK_DIR}/include)
include_directories(SYSTEM ${GTEST_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add executable
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
add_executable(${PROJECT_NAME} main.cpp ${TEST_DIR}/Automatic_temperature_controller_test.cpp)

# Linking
target_link_libraries(${PROJECT_NAME} gmock_main src_temperature_controller_module)

# Create a simple configuration header
configure_file(config.h.in config.h)

# Include the configuration header in the build
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")
