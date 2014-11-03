#include <fstream>
#include "Operations.hpp"
#include "Context.hpp"

std::ofstream out("out.txt");

int main()
{
	//Pointer<Boolean> p = QuantForall<ObjectVar, Boolean>(ObjectVar("x"), Eq(Add((Inc(Zero)), Inc(Inc(Zero))), Mul(Inc(Inc(Inc(Zero))), Inc(Zero))));
	Context context;
	for (Pointer<Boolean> p : context.axioms)
	{
		out << p->toString() << std::endl;
	}

	std::cout << (context.axioms.at(1) == context.axioms.at(2)) << std::endl << (context.axioms.at(1) == context.axioms.at(1)) << std::endl;
	//std::cout << std::boolalpha << p->calc() << std::endl;
}
