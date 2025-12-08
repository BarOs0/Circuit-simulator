#pragma once

#include "Passive.hpp"

class Resistance : public Passive{

    public:

        Resistance(double r, unsigned int pnode, unsigned int nnode);

        std::complex<double> getAdmitance(double freqency) const override;

        Resistance operator+(const Resistance &other) const;

        Resistance& operator+=(const Resistance &other);

        Resistance operator||(const Resistance &other) const;

        Resistance& operator|=(const Resistance &other);
};