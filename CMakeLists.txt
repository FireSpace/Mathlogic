cmake_minimum_required(VERSION 2.8.4)
project(mathlogic2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
	main.cpp
	#Expressions.hpp
	)
add_executable(mathlogic2 ${SOURCE_FILES})