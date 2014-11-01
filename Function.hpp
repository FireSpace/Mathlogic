#pragma once

#include "Expressions.hpp"
#include "Name.hpp"

#include <functional>
#include <vector>

//Function :: V^n -> V
//Predicate :: D^n -> V
template <typename ... ArgsT>
class Operation<Boolean, ArgsT...> : public Expression<Boolean>
{
protected:
	const Name name;
	std::tuple<Pointer<ArgsT>...> args;

	std::function<Boolean(ArgsT...)> func;
	bool init;

	static const size_t arn = sizeof...(ArgsT);

public:
	Operation(Pointer<ArgsT>... args, Name name)
			: name(name)
			, args(args) {}

	Operation(Pointer<ArgsT>... args, Name name, std::function<Boolean(ArgsT...)> func)
			: args(args)
			, name(name)
			, func(func)
			, init(true) {}

	void setName(std::function<Boolean(ArgsT...)> func) { this->func = func; init = true; }

	virtual Boolean calc() const
	{
		assert(init);
		//DODELAT'
	}

	virtual std::string toString() const
	{
		std::string result = "(" + name.getName() + "(";
		for (int i = 0; i < arn; ++i)
		{
			result += (std::get<i>(args).toString() + ",");
		}
		result.at(result.length()-1) = ')';
		result += ")";
		return result;
	}
};


template <typename ... ArgsT>
using Function = Operation<Boolean, ArgsT...>

//Because we don't have a syntax like <typename ... Object> :/
template <typename ... ArgsT>
using Predicate = Operation<Boolean, ArgsT...>;