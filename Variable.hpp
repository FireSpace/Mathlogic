#pragma once

#include "Expressions.hpp"
#include "Name.hpp"
#include "Function.hpp"
#include "Term.hpp"

#include <iostream>
#include <memory>

class ProposVar : public Function<>
{
public:
	ProposVar(Name name, Boolean var)
		: Function<>(name, [var](){return var;}) {}

	ProposVar(std::string name, Boolean var)
		: Function<>(Name(name), [&var](){return var;}) {}

	ProposVar(Boolean var)
		: Function<>(Name(""), [var](){return var;}) {}

	ProposVar(std::string name)
		: Function<>(Name(name)) {}

	virtual std::string toString() const override
    {
        if (this->clearBit) return this->str;

        this->str = "(" + ((name.empty()) ? std::to_string(func()) : name.getName()) + ")";
        this->clearBit = true;

		return this->str;
	}

    virtual Boolean calc() const override
    {
        assert(init);
        return func();
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

class ObjectVar : public Term<>
{
public:
	ObjectVar(Name name, Object var)
		: Term<>(name, [var](){return var;}) {}

	ObjectVar(std::string name, Object var)
		: Term<>(name, [var](){return var;}) {}

	ObjectVar(Object var)
		: Term<>(Name(""), [var](){return var;}) {}

	ObjectVar(std::string name)
		: Term<>(Name(name)) {}

	ObjectVar(Name name)
		: Term<>(name) {}

	virtual std::string toString() const override
	{
        return "(" + ((name.empty()) ? std::to_string(func()) : name.getName()) + ")";
	}

    virtual Object calc() const override
    {
        assert(init);
        return func();
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

Pointer<Boolean> PropVar(std::string name) { return std::make_shared<ProposVar>(name); }
Pointer<Object> ObjVar(std::string name) { return std::make_shared<ObjectVar>(name); }


const Pointer<Boolean> True = std::make_shared<ProposVar>(Name("True"), true);
const Pointer<Boolean> False = std::make_shared<ProposVar>(Name("False"), false);
const Pointer<Object> Zero = std::make_shared<ObjectVar>(0);
