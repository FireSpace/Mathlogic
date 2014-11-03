#pragma once

#include "Expressions.hpp"
#include "Term.hpp"
#include "Name.hpp"

#include <memory>

// Addition :: Object -> Object -> Object
class Addition : public Term<Object, Object>
{
public:
	Addition(Pointer<Object> arg1, Pointer<Object> arg2)
        : Term<Object, Object>(Name("Add"), [](Object a1, Object a2){return a1 + a2;}, arg1, arg2) {}


	virtual Object calc() const override;
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

Object Addition::calc() const
{
	return std::get<0>(args)->calc() + std::get<1>(args)->calc();
}

std::string Addition::toString() const
{
	if (this->clearBit) return this->str;

	this->str = "(" + std::get<0>(args)->toString() + "+" + std::get<1>(args)->toString() + ")";
	this->clearBit = true;

	return this->str;
}

Pointer<Object> Add(Pointer<Object> arg1, Pointer<Object> arg2)
{
	return std::make_shared<Addition>(arg1, arg2);
}
