#include "Capacitance.hpp"

Capacitance::Capacitance(double c, unsigned int pnode, unsigned int nnode)
                    : Passive(c, pnode, nnode, 'C'){}

std::complex<double> Capacitance::getAdmitance(double frequency) const {
    return std::complex<double>(0.0, (2 * M_PI * frequency) * (m_value));
}