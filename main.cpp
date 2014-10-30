#include <iostream>
#include "Operations.hpp"

int main()
{
	Pointer<Boolean> p = Eq(Add((Inc(Zero)), Inc(Inc(Zero))), Mul(Inc(Inc(Zero)), Inc(Zero)));
	std::cout << p->toString() << std::endl;
	std::cout << p->calc() << std::endl;
}