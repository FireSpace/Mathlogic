#pragma once

#include "Expressions.hpp"
#include "Function.hpp"
#include "Variable.hpp"

#include <functional>
#include <memory>

// type :: true — forall
//         false — exist
template <bool type, typename ... ArgsT>
class Quantifier : public Function<ArgsT...>
{
private:
    ObjectVar var;
    const std::function<Boolean(ArgsT...)> defaultFunc = [](ArgsT...){ return true; };
public:
    Quantifier(ObjectVar var, Pointer<ArgsT>... args)
        : Function<ArgsT...>("", defaultFunc, args...)
        , var(var) {}

    Quantifier(ObjectVar var, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
        : Function<ArgsT...>("", func, args...)
        , var(var) {}

    virtual std::string toString() const override
    {
        return (type ? "@" : "?") + var.toString() + "(" + this->caller(typename gens<sizeof...(ArgsT)>::type()) + ")";
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
    return std::make_shared<Quantifier<true, ArgsT...>>(ObjectVar(Name(name)), args...);
}

template <typename ... ArgsT>
Pointer<Boolean> QuantExist(std::string name, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<false, ArgsT...>>(ObjectVar(Name(name)), func, args...);
}

template <typename ... ArgsT>
Pointer<Boolean> QuantExist(std::string name, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<false, ArgsT...>>(ObjectVar(Name(name)), args...);
}

template <typename ... ArgsT>
Pointer<Boolean> QuantForall(std::string name, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<true, ArgsT...>>(ObjectVar(Name(name)), func, args...);
}
