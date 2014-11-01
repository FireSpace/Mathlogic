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
	Name name;
	std::tuple<Pointer<ArgsT>...> args;

	std::function<Boolean(ArgsT...)> func;
	bool init;

	static const size_t arn = sizeof...(ArgsT);

	/*Operation() //???? Tak li?
			: name("")
			, args()
			, func()
			, init(false) {}

	/*template<int ... S>
	std::string getStringTuple(seq<S...>)
	{
		return std::get<S>(args)->toString();
	}*/

public:
	virtual ~Operation() = default;

	Operation(Name name, Pointer<ArgsT>... args)
			: name(name)
			, args(args...) {}

	Operation(Name name, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
            : name(name)
            , args(args...)
			, func(func)
			, init(true) {}

	Operation(std::string name, Pointer<ArgsT>... args)
			: name(name)
			, args(args...) {}

	Operation(std::string, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
            : name(name)
            , args(args...)
			, func(func)
            , init(true) {}

	void setName(std::function<Boolean(ArgsT...)> func) { this->func = func; init = true; }

    virtual Boolean calc() const override = 0;
    /*{
		assert(init);
		//DODELAT'
		//Ne zabyd', chto nakosyachil v Variable.hpp (args not init)
		return true;
    }*/

    virtual std::string toString() const override = 0;
    /*{
        std::string result = "(" + name.getName() + "(";

		//Do not work
        for (int i = 0; i < arn; ++i)
		{
			result += (std::get<i>(args)->toString() + ",");
        }
		result.at(result.length()-1) = ')';
		result += ")";
        return result;
    }*/
};


template <typename ... ArgsT>
using Function = Operation<Boolean, ArgsT...>;

//Because we don't have a syntax like <typename ... Object> :/
template <typename ... ArgsT>
using Predicate = Operation<Boolean, ArgsT...>;
