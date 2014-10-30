#pragma once

#include "Expressions.hpp"

#include <memory>

//Negation :: Boolean -> Boolean
class Negation : public Unary<Boolean, Boolean>
{
public:
	Negation(Pointer<Boolean> arg)
			: Unary<Boolean, Boolean>(arg) {}

	virtual Boolean calc() const override
	{
		return !(std::get<0>(args))->calc();
	}


	virtual std::string toString() const override
	{
		return "(!" + (std::get<0>(args))->toString() + ")";
	}
};

Pointer<Boolean> Neg(Pointer<Boolean> arg)
{
	return std::make_shared<Negation>(arg);
}