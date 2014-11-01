#pragma once

#include "Expressions.hpp"
#include "Name.hpp"
#include "Function.hpp"
#include "Term.hpp"

#include <iostream>

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
        return "(" + ((name.empty()) ? std::to_string(func()) : name.getName()) + ")";
	}

    virtual Boolean calc() const override
    {
        assert(init);
        return func();
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
};



//Variable (maybe constant)
//Type — variable type
//True, False and Zero constant (nullary function)
/*template <typename Type>
class Variable : public Expression<Type>
{
protected:
	Type var;
	Name name;

	bool init;

public:
	Variable(Type var)
			: var(var)
			, name("")
			, init(true) {}

	Variable(std::string name)
			: name(name) {}

	Variable(Type var, std::string name)
			: var(var)
			  , name(name)
			  , init(true) {}

	virtual Type calc() const override
	{
		assert(init);

		return var;
	}

	virtual std::string toString() const override
	{
		if (name.empty()) return "(" + std::to_string(var) + ")";
		else return "(" + name.getName() + ")";
	}
};
*/

const Pointer<Boolean> True = std::make_shared<ProposVar>(Name("True"), true);
const Pointer<Boolean> False = std::make_shared<ProposVar>(Name("False"), false);
const Pointer<Object> Zero = std::make_shared<ObjectVar>(0);
