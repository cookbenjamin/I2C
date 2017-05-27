cmake_minimum_required(VERSION 3.6)
project(I2C)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
        src/I2cDevice.cpp
        src/I2cBus.cpp)