#pragma once

#include "Passive.hpp"

class Resistance : public Passive{

    public:

        Resistance(double r, unsigned int pnode, unsigned int nnode);

        std::complex<double> getAdmitance(double freqency) const override;
};