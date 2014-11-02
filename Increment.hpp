#pragma once

#include "Expressions.hpp"
#include "Term.hpp"
#include "Name.hpp"

#include <memory>

// Increment :: Object -> Object
class Increment : public Term<Object>
{
public:
	Increment(Pointer<Object> arg)
        : Term<Object>(Name("Inc"), [](Object a){ return a++; }, arg) {}


	virtual Object calc() const override;
	virtual std::string toString() const override;
};

Object Increment::calc() const
{
	return std::get<0>(args)->calc() + 1;
}

std::string Increment::toString() const
{
	if (this->clearBit) return this->str;

	this->str = "(" + std::get<0>(args)->toString() + "')";
	this->clearBit = true;

	return this->str;
}

Pointer<Object> Inc(Pointer<Object> arg)
{
	return std::make_shared<Increment>(arg);
}
