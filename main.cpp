#include <iostream>
#include "Operations.hpp"

int main()
{
	Pointer<Boolean> p = QuantForall<Boolean>("x", Eq(Add((Inc(Zero)), Inc(Inc(Zero))), Mul(Inc(Inc(Inc(Zero))), Inc(Zero))));
	std::cout << p->toString() << std::endl;
	std::cout << std::boolalpha << p->calc() << std::endl;
}
