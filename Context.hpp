#pragma once

#include "Operations.hpp"

#include <vector>

class Context
{
    void makeAxioms()
    {
        propAxioms.push_back(Impl(PropVar("a"), Impl(PropVar("b"), PropVar("a"))));
        propAxioms.push_back(Impl(Impl(PropVar("a"), PropVar("b")), Impl(Impl(PropVar("a"), Impl(PropVar("b"), PropVar("c"))), Impl(PropVar("a"), PropVar("c")))));
        propAxioms.push_back(Impl(PropVar("a"), Impl(PropVar("b"), Conj(PropVar("a"), PropVar("b")))));
        propAxioms.push_back(Impl(Conj(PropVar("a"), PropVar("b")), PropVar("a")));
        propAxioms.push_back(Impl(Conj(PropVar("a"), PropVar("b")), PropVar("b")));
        propAxioms.push_back(Impl(PropVar("a"), Disj(PropVar("a"), PropVar("b"))));
        propAxioms.push_back(Impl(Impl(PropVar("a"), PropVar("c")), Impl(Impl(PropVar("b"), PropVar("c")), Impl(Disj(PropVar("a"), PropVar("b")), PropVar("c")))));
        propAxioms.push_back(Impl(Impl(PropVar("a"), PropVar("b")), Impl(Impl(PropVar("a"), Neg(PropVar("b"))), Neg(PropVar("a")))));
        propAxioms.push_back(Impl(Neg(Neg(PropVar("a"))), PropVar("a")));
    }

public:

    std::vector<Pointer<Boolean>> propAxioms;
    std::vector<Pointer<Boolean>> objAxioms;

    std::vector<Pointer<Boolean>> propAssump;
    std::vector<Pointer<Object>> objAssump;

    Context() { makeAxioms(); }
};
