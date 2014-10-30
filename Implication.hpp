#pragma once

#include "Expressions.hpp"

#include <memory>

//Implication :: Boolean -> Boolean -> Boolean
class Implication : public Binary<Boolean, Boolean, Boolean>
{
public:
	Implication(Pointer<Boolean> arg1, Pointer<Boolean> arg2)
		: Binary<Boolean, Boolean, Boolean>(arg1, arg2) {}


	virtual Boolean calc() const override;
	virtual std::string toString() const override;
};

Boolean Implication::calc() const
{
	auto arg1 = std::get<0>(args);
	auto arg2 = std::get<1>(args);
	return !arg1->calc() || arg2->calc();
}

std::string Implication::toString() const
{
	return "(" + std::get<0>(args)->toString() + "→" + std::get<1>(args)->toString() + ")";
}

Pointer<Boolean> Impl(Pointer<Boolean> arg1, Pointer<Boolean> arg2)
{
	std::make_shared<Implication>(arg1, arg2);
}