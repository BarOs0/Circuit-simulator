#pragma once

#include "Element.hpp"

class Passive : public Element{

    public: 

        virtual ~Passive() = default;

    protected:

        Passive(double val, unsigned int pnode, unsigned int nnode, char type);

        virtual std::complex<double> getAdmitance(double frequency) const = 0;
};