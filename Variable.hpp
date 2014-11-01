#pragma once

#include "Expressions.hpp"
#include "Name.hpp"
#include "Function.hpp"
#include "Term.hpp"

class ProposVar : Function<>
{
public:
	ProposVar(Name name, Boolean var)
			: name(name)
			, func([var](){return var;}) {}

	ProposVar(std::string name, Boolean var)
			: name(name)
			, func([var](){return var;}) {}

	ProposVar(Boolean var)
			: func([var](){return var;}) {}

	virtual std::string toString() const override
	{
		return "(" + name.getName().empty() ? std::to_string(func()) : name.getName() + ")";
	}
};

class ObjectVar : Term<>
{
public:
	ObjectVar(Name name, Object var)
			: name(name)
			, func([var](){return var;}) {}

	ObjectVar(std::string name, Object var)
			: name(name)
			, func([var](){return var;}) {}

	ObjectVar(Object var)
			: func([var](){return var;}) {}

	virtual std::string toString() const override
	{
		return "(" + name.getName().empty() ? std::to_string(func()) : name.getName() + ")";
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

const Pointer<Boolean> True = std::make_shared<ProposVar>("True", true);
const Pointer<Boolean> False = std::make_shared<ProposVar>("False", false);
const Pointer<Object> Zero = std::make_shared<ObjectVar>(0);