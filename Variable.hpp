#pragma once

#include "Expressions.hpp"

//Variable (maybe constant)
//Type — variable type
//True, False and Zero constant (nullary function)
template <typename Type>
class Variable : public Expression<Type>
{
protected:
	Type var;
	std::string name;

	bool init;

public:
	Variable(Type var)
			: var(var)
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
		if (name.empty()) return std::to_string(var);
		else return name;
	}
};

const Pointer<Boolean> True = std::make_shared<Variable<Boolean>>(true, "True");
const Pointer<Boolean> False = std::make_shared<Variable<Boolean>>(false, "False");
const Pointer<Object> Zero = std::make_shared<Variable<Object>>(0);