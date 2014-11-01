#pragma once

#include "string"

//Name of a function or object variable or propositional variable or predicate
class Name
{
	const std::string name;

public:
	Name(std::string name)
			: name(name) {}

	std::string getName() const { return name; }
	bool empty() const { return name.empty(); }
};