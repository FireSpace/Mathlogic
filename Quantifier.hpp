#pragma once

#include "Expressions.hpp"
#include "Function.hpp"
#include "Variable.hpp"
#include "Name.hpp"

#include <functional>
#include <memory>
#include <vector>

// type :: true — forall
//         false — exist
template <bool type, typename VarT, typename ... ArgsT>
class Quantifier : public Function<ArgsT...>
{
private:
    VarT var;
    //const std::function<Boolean(ArgsT...)> defaultFunc = [](ArgsT ... args){ return true; };
    std::function<Boolean(ArgsT...)> defaultFunc ( ) { return [](ArgsT ... args){ return true; }; }
public:
    Quantifier(VarT var, Pointer<ArgsT>... args)
        : Function<ArgsT...>(Name(""), defaultFunc(), args...)
        , var(var) {}

    Quantifier(VarT var, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
        : Function<ArgsT...>(Name(""), func, args...)
        , var(var) {}

    virtual std::string toString() const override
    {
        if (this->clearBit) return this->str;

        this->str = (type ? "(@" : "(?") + var.toString() + "(" + this->callerToString(typename gens<sizeof...(ArgsT)>::type()) + "))";
        this->clearBit = true;

        return this->str;
    }

    virtual void substitution(Pointer<Boolean> from, Pointer<Boolean> to) override
    {
        this->subst(from, to);
    }

    virtual void substitution(Pointer<Object> from, Pointer<Object> to) override
    {
        this->subst(from, to);
    }

    virtual Boolean calc() const override
    {
        assert(this->init);
        return this->callerCalc(typename gens<sizeof...(ArgsT)>::type());
    }
};


template <typename VarT, typename ... ArgsT>
using Forall = Quantifier<true, VarT, ArgsT...>;

template <typename VarT, typename ... ArgsT>
using Exist = Quantifier<false, VarT, ArgsT...>;

template <typename VarT, typename ... ArgsT>
Pointer<Boolean> QuantForall(VarT var, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<true, VarT, ArgsT...>>(var, args...);
}

template <typename VarT, typename ... ArgsT>
Pointer<Boolean> QuantExist(VarT var, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<false, VarT, ArgsT...>>(var, func, args...);
}

template <typename VarT, typename ... ArgsT>
Pointer<Boolean> QuantExist(VarT var, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<false, VarT, ArgsT...>>(var, args...);
}

template <typename VarT, typename ... ArgsT>
Pointer<Boolean> QuantForall(VarT var, std::function<Boolean(ArgsT...)> func, Pointer<ArgsT>... args)
{
    return std::make_shared<Quantifier<true, VarT, ArgsT...>>(var, func, args...);
}
