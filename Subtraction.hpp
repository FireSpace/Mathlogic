#pragma once

#include "Expressions.hpp"
#include "Term.hpp"
#include "Name.hpp"

#include <memory>

// Subtraction :: Object -> Object -> Object
class Subtraction : public Term<Object, Object>
{
public:
	Subtraction(Pointer<Object> arg1, Pointer<Object> arg2)
        : Term<Object, Object>(Name("Substr"), [](Object a1, Object a2){ return a1 - a2; }, arg1, arg2) {}


	virtual Object calc() const override;
	virtual std::string toString() const override;
};

Object Subtraction::calc() const
{
	return (std::get<0>(args)->calc() - std::get<1>(args)->calc());
}

std::string Subtraction::toString() const
{
	if (this->clearBit) return this->str;

	this->str = "(" + std::get<0>(args)->toString() + "-" + std::get<1>(args)->toString() + ")";
	this->clearBit = true;

	return this->str;
}

Pointer<Object> Subtract(Pointer<Object> arg1, Pointer<Object> arg2)
{
	return std::make_shared<Subtraction>(arg1, arg2);
}
