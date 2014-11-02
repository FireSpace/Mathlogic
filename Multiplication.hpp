#pragma once

#include "Expressions.hpp"
#include "Term.hpp"
#include "Name.hpp"

#include <memory>

// Multiplication :: Object -> Object -> Object
class Multiplication : public Term<Object, Object>
{
public:
	Multiplication(Pointer<Object> arg1, Pointer<Object> arg2)
        : Term<Object, Object>(Name("Mul"), [](Object a1, Object a2){ return a1 * a2; }, arg1, arg2) {}

	virtual Object calc() const override;
	virtual std::string toString() const override;
};

Object Multiplication::calc() const
{
	return std::get<0>(args)->calc() * std::get<1>(args)->calc();
}

std::string Multiplication::toString() const
{
	if (this->clearBit) return this->str;

	this->str = "(" + std::get<0>(args)->toString() + "*" + std::get<1>(args)->toString() + ")";
	this->clearBit = true;

	return this->str;
}

Pointer<Object> Mul(Pointer<Object> arg1, Pointer<Object> arg2)
{
	return std::make_shared<Multiplication>(arg1, arg2);
}
