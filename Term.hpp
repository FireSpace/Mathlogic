#pragma once

#include "Expressions.hpp"
#include "Name.hpp"

#include <functional>
#include <vector>
#include <memory>

class ProposVar;
class ObjectVar;

//Term :: D^n -> D
template <typename ... ArgsT>
class Operation<Object, ArgsT...> : public Expression<Object>
{
protected:
	Name name;
	std::tuple<Pointer<ArgsT>...> args;

	std::function<Object(ArgsT...)> func;
	bool init;

	mutable std::string str;
	mutable bool clearBit;

	static const size_t arn = sizeof...(ArgsT);

//---------------------------------------------------------------------------------------------------
//For tuple
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
	std::string callerToString(seq<S...>) const
	{
		std::string result = allArgsToString(std::get<S>(args)...);
		if (result.length() != 0) result = result.substr(0, result.length()-1);
		return result;
	}

	template <int ... S>
	Object callerCalc(seq<S...>) const
	{
		return func(std::get<S>(args)->calc()...);
	}

	template <typename T>
	void finalSubst(Pointer<T> from, Pointer<T> to) {}

	template<typename A, typename ... B, typename T>
	void finalSubst(Pointer<T> from, Pointer<T> to, A a, B ... b)
	{
		a->substitution(from, to);
		finalSubst(from, to, b...);
	}

	template <typename A, typename ... B, typename T>
	void finalSubst(Pointer<T> from, Pointer<T> to, Pointer<T> a, B ... b)
	{
		if (from == a)
		{
			a = to;
			to->toString();
		}
		a->substitution(from, to);

		finalSubst(from, to, b...);
	}

	template <int ... S, typename T>
	void callerSubst(Pointer<T> from, Pointer<T> to, seq<S...>)
	{
		finalSubst(from, to, std::get<S>(args)...);
	}
//---------------------------------------------------------------------------------------------------

	template <typename T>
	void subst(Pointer<T> from, Pointer<T> to)
	{
		callerSubst(from, to, typename gens<sizeof...(ArgsT)>::type());
	}

public:
	std::vector<ProposVar> boundPropVars;
	std::vector<ObjectVar> boundObjVars;

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

    virtual Object calc() const
    {
		assert(init);
		return callerCalc(typename gens<sizeof...(ArgsT)>::type());
	}

    virtual std::string toString() const override
    {
        if (clearBit) return str;

        std::string result = "(" + name.getName() + "(";
		result += callerToString(typename gens<sizeof...(ArgsT)>::type());
		result += "))";

		str = result;
		clearBit = true;

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
