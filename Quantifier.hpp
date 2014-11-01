#pragma once

#include "Expressions.hpp"
#include "Function.hpp"
#include "Variable.hpp"

#include <functional>

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
        return (type ? "@" : "?") + var.toString() + "(" + allArgsToString() + ")";
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
