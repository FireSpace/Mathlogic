#pragma once

#include "Expressions.hpp"
#include "Function.hpp"
#include "Variable.hpp"
#include "Name.hpp"

#include <functional>
#include <memory>

// type :: true — forall
//         false — exist
template <bool type, typename ... ArgsT>
class Quantifier : public Function<ArgsT...>
{
private:
    Name var;
    const std::function<Boolean(ArgsT...)> defaultFunc = [](ArgsT...){ return true; };
public:
    Quantifier(Name var, Pointer<ArgsT>... args)
        : Function<ArgsT...>(Name(""), defaultFunc, args...)
        , var(var) {}

    Quantifier(Name var, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
        : Function<ArgsT...>(Name(""), func, args...)
        , var(var) {}

    virtual std::string toString() const override
    {
        return (type ? "(@" : "(?") + var.getName() + "(" + this->caller(typename gens<sizeof...(ArgsT)>::type()) + "))";
    }

    virtual Boolean calc() const override
    {
        //???
    }
};


template <typename ... ArgsT>
using Forall = Quantifier<true, ArgsT...>;

template <typename ... ArgsT>
using Exist = Quantifier<false, ArgsT...>;

template <typename ... ArgsT>
Pointer<Boolean> QuantForall(std::string name, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<true, ArgsT...>>((Name(name)), args...);
}

template <typename ... ArgsT>
Pointer<Boolean> QuantExist(std::string name, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<false, ArgsT...>>((Name(name)), func, args...);
}

template <typename ... ArgsT>
Pointer<Boolean> QuantExist(std::string name, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<false, ArgsT...>>((Name(name)), args...);
}

template <typename ... ArgsT>
Pointer<Boolean> QuantForall(std::string name, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<true, ArgsT...>>((Name(name)), func, args...);
}
