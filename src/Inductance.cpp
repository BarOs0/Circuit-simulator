#include "Inductance.hpp"

Inductance::Inductance(double l, unsigned int pnode, unsigned int nnode)
                    : Passive(l, pnode, nnode, 'L'){}

std::complex<double> Inductance::getAdmitance(double frequency) const {
    return std::complex<double>(0.0, (-1) / ((2 * M_PI * frequency) * (m_value)));
}