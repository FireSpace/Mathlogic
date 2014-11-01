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

public:
	std::vector<ProposVar> boundPropVars;
	std::vector<ObjectVar> boundObjVars;

	Operation(Name name, Pointer<ArgsT>... args, std::vector<ProposVar> boundPropVars = std::vector<ProposVar>(), std::vector<ObjectVar> boundObjVars = std::vector<ObjectVar>())
			: name(name)
			, args(args...)
			, boundPropVars(boundPropVars)
			, boundObjVars(boundObjVars) {}

	Operation(Name name, std::function<Object(ArgsT...)> func, Pointer<ArgsT>... args, std::vector<ProposVar> boundPropVars = std::vector<ProposVar>(), std::vector<ObjectVar> boundObjVars = std::vector<ObjectVar>())
			: name(name)
			, args(args...)
			, func(func)
			, init(true)
			, boundPropVars(boundPropVars)
			, boundObjVars(boundObjVars) {}

	Operation(std::string name, Pointer<ArgsT>... args, std::vector<ProposVar> boundPropVars = std::vector<ProposVar>(), std::vector<ObjectVar> boundObjVars = std::vector<ObjectVar>())
			: name(name)
			, args(args...)
			, boundPropVars(boundPropVars)
			, boundObjVars(boundObjVars) {}

	Operation(std::string name, std::function<Object(ArgsT...)> func, Pointer<ArgsT>... args, std::vector<ProposVar> boundPropVars = std::vector<ProposVar>(), std::vector<ObjectVar> boundObjVars = std::vector<ObjectVar>())
			: name(name)
			, args(args...)
			, func(func)
			, init(true)
			, boundPropVars(boundPropVars)
			, boundObjVars(boundObjVars) {}

	void setName(std::function<Object(ArgsT...)> func) { this->func = func; init = true; }

    virtual Object calc() const
    {
		assert(init);
		return callerCalc(typename gens<sizeof...(ArgsT)>::type());
	}

    virtual std::string toString() const override
    {
        std::string result = "(" + name.getName() + "(";

		result += callerToString(typename gens<sizeof...(ArgsT)>::type());
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
