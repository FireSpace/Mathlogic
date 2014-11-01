cmake_minimum_required(VERSION 2.8.4)
project(mathlogic2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(SOURCE_FILES
	main.cpp
	Expressions.hpp
	Addition.hpp
	Conjunction.hpp
	Disjunction.hpp
	Equal.hpp
	Implication.hpp
	Increment.hpp
	Multiplication.hpp
	Negation.hpp
	Operations.hpp
	Subtraction.hpp
	Variable.hpp
	Name.hpp
	Function.hpp
	Term.hpp
	Quantifier.hpp
	Context.hpp
	)
add_executable(mathlogic2 ${SOURCE_FILES})
