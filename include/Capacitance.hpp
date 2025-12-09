#pragma once

#include "Passive.hpp"

namespace bo{

    class Capacitance : public Passive{

        public:

            Capacitance(double c, unsigned int pnode, unsigned int nnode);

            std::complex<double> getAdmitance(double frequency) const override;

            Capacitance operator+(const Capacitance &other) const;

            Capacitance& operator+=(const Capacitance &other);

            Capacitance operator||(const Capacitance &other) const;

            Capacitance& operator|=(const Capacitance &other);
    };

}