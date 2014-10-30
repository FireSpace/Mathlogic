#pragma once

#include "Expressions.hpp"

#include <memory>

// Increment :: Object -> Object
class Increment : public Unary<Object, Object>
{
public:
	Increment(Pointer<Object> arg)
		: Unary<Object, Object>(arg) {}


	virtual Object calc() const override;
	virtual std::string toString() const override;
};

Object Increment::calc() const
{
	return std::get<0>(args)->calc() + 1;
}

std::string Increment::toString() const
{
	return "(" + std::get<0>(args)->toString() + "')";
}

Pointer<Object> Inc(Pointer<Object> arg)
{
	return std::make_shared<Increment>(arg);
}