#pragma once

#include "Expressions.hpp"
#include "Name.hpp"

#include <functional>
#include <vector>

//Term :: D^n -> D
template <typename ... ArgsT>
class Operation<Object , ArgsT...> : public Expression<Object>
{
protected:
	const Name name;
	std::tuple<Pointer<ArgsT>...> args;

	std::function<Object(ArgsT...)> func;
	bool init;

	static const size_t arn = sizeof...(ArgsT);

	Operation() //???? Tak li?
			: name("")
			, args()
			, func()
			, init(false) {}

public:
	Operation(Name name, Pointer<ArgsT>... args)
			: name(name)
			, args(args) {}

	Operation(Name name, std::function<Object(ArgsT...)> func, Pointer<ArgsT>... args)
			: args(args)
			, name(name)
			, func(func)
			, init(true) {}

	Operation(std::string name, Pointer<ArgsT>... args)
			: name(name)
			, args(args) {}

	Operation(std::string name, std::function<Object(ArgsT...)> func, Pointer<ArgsT>... args)
			: args(args)
			, name(name)
			, func(func)
			, init(true) {}

	void setName(std::function<Object(ArgsT...)> func) { this->func = func; init = true; }

	virtual Object calc() const
	{
		assert(init);
		//DODELAT'
		//Ne zabyd', chto nakosyachil v Variable.hpp (args not init)
		return true;
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


//Term
template <typename ... ArgsT>
using Term = Operation<Object, ArgsT...>;