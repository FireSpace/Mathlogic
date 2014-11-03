#pragma once

#include <memory>
#include <string>
#include <inttypes.h>
#include <assert.h>

//Operation type
typedef bool Boolean;
typedef int64_t Object;

//-------------------------------------------------------------------------------------------
//Expression & Pointer
//Type — expression type (type of output argument)

template <typename Type>
class Expression
{
public:
	virtual Type calc() const = 0;

	virtual std::string toString() const = 0;
	
	//2 overloads becouse templates may not be virtual
	virtual void substitution(std::shared_ptr<Expression<Boolean>>, std::shared_ptr<Expression<Boolean>> to) = 0;
	virtual void substitution(std::shared_ptr<Expression<Object> >, std::shared_ptr<Expression<Object> > to) = 0;
};

template <typename Type>
using Pointer = std::shared_ptr<Expression<Type>>;

template <typename T1, typename T2>
bool operator ==(Pointer<T1> p1, Pointer<T2> p2)
{
	return false;
}

template <typename T1, typename T2>
bool operator ==(Pointer<T1> p1, Pointer<T1> p2)
{
	return p1->toString() == p2->toString();
}

//-------------------------------------------------------------------------------------------
//Abstract Operation
//Arn — number of input arguments
//Type — type of output argument (operation type)
//ArgsT — tuple of input parameters types

template <typename Type, typename ... ArgsT>
class Operation : public Expression<Type>
{
protected:
	std::tuple<Pointer<ArgsT>...> args;
	static const size_t arn = sizeof...(ArgsT);

public:
	~Operation() = default;

	virtual Type calc() const override = 0;

	virtual std::string toString() const override = 0;

	virtual void substitution(Pointer<Boolean>, Pointer<Boolean> to) override = 0;
	virtual void substitution(Pointer<Object>, Pointer<Object> to) override = 0;
};

//Unary operations
//template <typename Type, typename ArgT>
//using Unary = Operation<Type, ArgT>;

//Binary operations
//template <typename Type, typename Arg1T, typename Arg2T>
//using Binary = Operation<Type, Arg1T, Arg2T>;

//Some utility
template <int ...>
struct seq { };

template<int N, int ... S>
struct gens : gens<N-1, N-1, S...> {};

template<int ... S>
struct gens<0, S...>
{
	typedef seq<S...> type;
};
