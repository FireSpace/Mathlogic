#include <iostream>
#include <string>

#include "Operations.hpp"

std::string to_string(bool b)
{
	return b ? "True" : "False";
}

int main()
{
	Pointer<Boolean> p = Eq(Add((Inc(Zero)), Inc(Inc(Zero))), Mul(Inc(Inc(Inc(Zero))), Inc(Zero)));
	std::cout << p->toString() << std::endl;
	std::cout << to_string(p->calc()) << std::endl;
}
