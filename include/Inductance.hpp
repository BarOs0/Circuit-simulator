#pragma once

#include "Passive.hpp"

namespace bo{

    class Inductance : public Passive{

        public:

            Inductance(double l, unsigned int pnode, unsigned int nnode);

            std::complex<double> getAdmitance(double frequency) const override;

            Inductance operator+(const Inductance &other) const;

            Inductance& operator+=(const Inductance &other);

            Inductance operator||(const Inductance &other) const;

            Inductance& operator|=(const Inductance &other);
    };

}