#include "Resistance.hpp"

Resistance::Resistance(double r, unsigned int pnode, unsigned int nnode)
                    : Passive(r, pnode, nnode, 'R'){}

std::complex<double> Resistance::getAdmitance(double) const {
    return std::complex<double>((1 / (m_value)), 0.0);
}