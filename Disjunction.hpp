#pragma once

#include "Expressions.hpp"
#include "Function.hpp"
#include "Name.hpp"

#include <memory>

//Disjunction :: Boolean -> Boolean -> Boolean
class Disjunction : public Function<Boolean, Boolean>
{
public:
	Disjunction(Pointer<Boolean> arg1, Pointer<Boolean> arg2)
        : Function<Boolean, Boolean>(Name("Disj"), [](Boolean a1, Boolean a2){ return a1 || a2; }, arg1, arg2) {}

	virtual Boolean calc() const override;
	virtual std::string toString() const override;

    virtual void substitution(const Pointer<Boolean>& from, const Pointer<Boolean>& to) override
    {
        this->subst(from, to);
    }

    virtual void substitution(const Pointer<Object>& from, const Pointer<Object>& to) override
    {
        this->subst(from, to);
    }
};

Boolean Disjunction::calc() const
{
	return (std::get<0>(args))->calc() || (std::get<1>(args))->calc();
}

std::string Disjunction::toString() const
{
	if (this->clearBit) return this->str;

	this->str = "(" + (std::get<0>(args))->toString() + "|" + (std::get<1>(args))->toString() + ")";
	this->clearBit = true;

	return str;
}

Pointer<Boolean> Disj(Pointer<Boolean> arg1, Pointer<Boolean> arg2)
{
	return std::make_shared<Disjunction>(arg1, arg2);
}
