#include <iostream>
#include "Operations.hpp"

int main()
{
	Pointer<Boolean> p = QuantForall<ObjectVar, Boolean>(ObjectVar("x"), Eq(Add((Inc(Zero)), Inc(Inc(Zero))), Mul(Inc(Inc(Inc(Zero))), Inc(Zero))));
	std::cout << p->toString() << std::endl;
	std::cout << std::boolalpha << p->calc() << std::endl;
}
