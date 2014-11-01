#pragma once

#include "Expressions.hpp"
#include "Name.hpp"

#include <functional>
#include <vector>
#include <memory>

//Term :: D^n -> D
template <typename ... ArgsT>
class Operation<Object, ArgsT...> : public Expression<Object>
{
protected:
	Name name;
	std::tuple<Pointer<ArgsT>...> args;

	std::function<Object(ArgsT...)> func;
	bool init;

	static const size_t arn = sizeof...(ArgsT);

	template <typename T>
	std::string argToString(Pointer<T> arg) const
	{
		return arg->toString();
	}

	std::string allArgsToString() const { return ""; }

	template <typename A, typename ... B>
	std::string allArgsToString(A a, B ... b) const
	{
		return argToString(a) + "," + allArgsToString(b...);
	}

	template<int ... S>
	std::string caller(seq<S...>) const
	{
		std::string result = allArgsToString(std::get<S>(args)...);
		if (result.length() != 0) result = result.substr(0, result.length()-1);
		return result;
	}

public:
	Operation(Name name, Pointer<ArgsT>... args)
			: name(name)
			, args(args...) {}

	Operation(Name name, std::function<Object(ArgsT...)> func, Pointer<ArgsT>... args)
			: name(name)
			, args(args...)
			, func(func)
			, init(true) {}

	Operation(std::string name, Pointer<ArgsT>... args)
			: name(name)
			, args(args...) {}

	Operation(std::string name, std::function<Object(ArgsT...)> func, Pointer<ArgsT>... args)
			: name(name)
			, args(args...)
			, func(func)
			, init(true) {}

	void setName(std::function<Object(ArgsT...)> func) { this->func = func; init = true; }

    virtual Object calc() const = 0;
    /*{
		assert(init);
		//DODELAT'
		//Ne zabyd', chto nakosyachil v Variable.hpp (args not init)
		return true;
	}*/

    virtual std::string toString() const override
    {
        std::string result = "(" + name.getName() + "(";

		//Do not work
		result += caller(typename gens<sizeof...(ArgsT)>::type());
		result += "))";
		return result;
	}
};


//Term
template <typename ... ArgsT>
using Term = Operation<Object, ArgsT...>;

template <typename ... ArgsT>
Pointer<Object> Ter(std::string name, Pointer<ArgsT>... args)
{
	return std::make_shared<Term<ArgsT...>>(Name(name), args...);
}

template <typename ... ArgsT>
Pointer<Object> Ter(std::string name, std::function<Object(ArgsT...)> func, Pointer<ArgsT>... args)
{
	return std::make_shared<Term<ArgsT...>>(Name(name), func, args...);
}
