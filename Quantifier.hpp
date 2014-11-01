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
    const std::function<Boolean(ArgsT...)> defaultFunc = [](){ return true; };
public:
    Quantifier(ObjectVar var, Pointer<ArgsT>... args)
        : Function<ArgsT...>("", defaultFunc, args...)
        , var(var) {}

    Quantifier(ObjectVar var, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT> args)
        : Function<ArgsT...>("", func, args)
        , var(var) {}

    virtual std::string toString() const override
    {
        return (type ? "@" : "?") + var.toString() + "(" + caller(typename gens<sizeof...(args)>::type()) + ")";
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
Pointer<Boolean> Quant(bool isForall, std::string name, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<isForall, ArgsT...>>(name, args...);
}

template <typename ... ArgsT>
Pointer<Boolean> Quant(bool isForall, std::string name, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT> args)
{
    return std::make_shared<Quantifier<isForall, ArgsT...>>(name, func, args...);
}
