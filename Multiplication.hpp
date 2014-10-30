#pragma once

#include "Expressions.hpp"

#include <memory>

// Multiplication :: Object -> Object -> Object
class Multiplication : public Binary<Object, Object, Object>
{
public:
	Multiplication(Pointer<Object> arg1, Pointer<Object> arg2)
		: Binary<Object, Object, Object>(arg1, arg2) {}

	virtual Object calc() const override;
	virtual std::string toString() const override;
};

Object Multiplication::calc() const
{
	return std::get<0>(args)->calc() * std::get<1>(args)->calc();
}

std::string Multiplication::toString() const
{
	return "(" + std::get<0>(args)->toString() + "*" + std::get<1>(args)->toString() + ")";
}

Pointer<Object> Mul(Pointer<Object> arg1, Pointer<Object> arg2)
{
	return std::make_shared<Multiplication>(arg1, arg2);
}