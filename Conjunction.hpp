#pragma once

#include "Expressions.hpp"

#include <memory>

//Conjunction :: Boolean -> Boolean -> Boolean
class Conjunction : public Binary<Boolean, Boolean, Boolean>
{
public:
	Conjunction(Pointer<Boolean> arg1, Pointer<Boolean> arg2)
			: Binary<Boolean, Boolean, Boolean>(arg1, arg2) {}


	virtual Boolean calc() const override;
	virtual std::string toString() const override;
};

Boolean Conjunction::calc() const
{
	return (std::get<0>(args))->calc() && (std::get<1>(args))->calc();
}

std::string Conjunction::toString() const
{
	return "(" + (std::get<0>(args))->toString() + "&" + (std::get<1>(args))->toString() + ")";
}

Pointer<Boolean> Conj(Pointer<Boolean> arg1, Pointer<Boolean> arg2)
{
	return std::make_shared<Conjunction>(arg1, arg2);
}