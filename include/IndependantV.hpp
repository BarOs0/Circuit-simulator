#pragma once

#include "Active.hpp"

class IndependantV : public Active{

    public:

        IndependantV(std::complex<double> v, unsigned int pnode, unsigned int nnode);
};