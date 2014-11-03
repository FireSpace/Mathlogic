#pragma once

#include "Expressions.hpp"
#include "Function.hpp"
#include "Name.hpp"

#include <memory>

//Negation :: Boolean -> Boolean
class Negation : public Function<Boolean>
{
public:
	Negation(Pointer<Boolean> arg)
            : Function<Boolean>(Name("Neg"), [](Boolean a){ return !a; }, arg) {}

	virtual Boolean calc() const override
	{
		return !(std::get<0>(args))->calc();
	}


	virtual std::string toString() const override
	{
		if (this->clearBit) return this->str;

		this->str = "(!" + (std::get<0>(args))->toString() + ")";
		this->clearBit = true;

		return this->str;
	}

    virtual void substitution(const Pointer<Boolean>& from, const Pointer<Boolean>& to) override
    {
        this->subst(from, to);
    }

    virtual void substitution(const Pointer<Object>& from, const Pointer<Object>& to) override
    {
        this->subst(from, to);
    }
};

Pointer<Boolean> Neg(Pointer<Boolean> arg)
{
	return std::make_shared<Negation>(arg);
}
