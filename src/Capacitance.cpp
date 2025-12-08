#include "Capacitance.hpp"

Capacitance::Capacitance(double c, unsigned int pnode, unsigned int nnode)
                    : Passive(c, pnode, nnode, 'C'){}

std::complex<double> Capacitance::getAdmitance(double frequency) const {
    return std::complex<double>(0.0, (2 * M_PI * frequency) * (m_value));
}

Capacitance Capacitance::operator+(const Capacitance &other) const {
    return Capacitance((this->m_value * other.m_value)/(this->m_value + other.m_value),
                        this->getEndpoints()[0], this->getEndpoints()[1]);
}

Capacitance& Capacitance::operator+=(const Capacitance &other){
    this->m_value = ((this->m_value*other.m_value)/(this->m_value + other.m_value));
    return *this;
}

Capacitance Capacitance::operator||(const Capacitance &other) const{
    return Capacitance(this->m_value + other.m_value, this->getEndpoints()[0], this->getEndpoints()[1]);
}

Capacitance& Capacitance::operator|=(const Capacitance &other){
    this->m_value += other.m_value;
    return *this;
}