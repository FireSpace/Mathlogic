#pragma once

#include "Expressions.hpp"

#include <memory>

// Equal :: Object -> Object -> Boolean
class Equal : public Predicate<Object, Object>
{
public:
	Equal(Pointer<Object> arg1, Pointer<Object> arg2)
		: Predicate<Object, Object>(arg1, arg2) {}


	virtual Boolean calc() const override;
	virtual std::string toString() const override;
};

Boolean Equal::calc() const
{
	return std::get<0>(args)->calc() == std::get<1>(args)->calc();
}

std::string Equal::toString() const
{
	return "(" + std::get<0>(args)->toString() + "=" + std::get<1>(args)->toString() + ")";
}

Pointer<Boolean> Eq(Pointer<Object> arg1, Pointer<Object> arg2)
{
	return std::make_shared<Equal>(arg1, arg2);
}