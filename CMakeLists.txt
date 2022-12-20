cmake_minimum_required(VERSION 3.10)

# Set some basic project attributes
project (Automatic_temperature_controller
	VERSION 0.1
	DESCRIPTION "An automatic temperature controller with google unit test project")
	
enable_testing()

include(CMakeDependentOption)
include(GNUInstallDirs)

#add_subdirectory( googletest )

# This project will output an executable file
##add_executable(${PROJECT_NAME} Automatic_temperature_controller.cpp temperature_controller_module.cpp)
add_executable(${PROJECT_NAME} main.cpp Automatic_temperature_controller.cpp temperature_controller_module.cpp)

# Create a simple configuration header
configure_file(config.h.in config.h)

# Include the configuration header in the build
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

######## GTest #################
include_directories(${CMAKE_SOURCE_DIR}/googletest/include/gtest)
find_library(Test_LIB_gtest gtest "${CMAKE_SOURCE_DIR}/libs")
find_library(Test_LIB_gtest_main gtest_main "${CMAKE_SOURCE_DIR}/libs")
target_link_libraries(${PROJECT_NAME} ${Test_LIB_gtest} ${Test_LIB_gtest_main})