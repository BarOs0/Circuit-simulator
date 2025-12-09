#pragma once

#include "Active.hpp"

namespace bo{

    class IndependantV : public Active{

        public:

            IndependantV(std::complex<double> v, unsigned int pnode, unsigned int nnode);
    };

}