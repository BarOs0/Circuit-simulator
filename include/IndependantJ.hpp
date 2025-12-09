#pragma once

#include "Active.hpp"

namespace bo{

    class IndependantJ : public Active{

        public:

            IndependantJ(std::complex<double> j, unsigned int pnode, unsigned int nnode);
    };

}