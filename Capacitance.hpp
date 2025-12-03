#pragma once

#include "Passive.hpp"

class Capacitance : public Passive{

    public:

        Capacitance(double c, unsigned int pnode, unsigned int nnode);

        std::complex<double> getAdmitance(double frequency) const override;
};