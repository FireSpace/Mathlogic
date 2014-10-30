#pragma once

#include "Expressions.hpp"

#include <memory>

//Disjunction :: Boolean -> Boolean -> Boolean
class Disjunction : public Binary<Boolean, Boolean, Boolean>
{
public:
	Disjunction(Pointer<Boolean> arg1, Pointer<Boolean> arg2)
		: Binary<Boolean, Boolean, Boolean>(arg1, arg2) {}

	virtual Boolean calc() const override;
	virtual std::string toString() const override;
};

Boolean Disjunction::calc() const
{
	return (std::get<0>(args))->calc() || (std::get<1>(args))->calc();
}

std::string Disjunction::toString() const
{
	return "(" + (std::get<0>(args))->toString() + "|" + (std::get<1>(args))->toString() + ")";
}

Pointer<Boolean> Disj(Pointer<Boolean> arg1, Pointer<Boolean> arg2)
{
	return std::make_shared<Disjunction>(arg1, arg2);
}