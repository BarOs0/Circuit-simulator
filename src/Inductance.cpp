#include "Inductance.hpp"

namespace bo{

    Inductance::Inductance(double l, unsigned int pnode, unsigned int nnode)
                        : Passive(l, pnode, nnode, 'L'){}

    std::complex<double> Inductance::getAdmitance(double frequency) const {
        return std::complex<double>(0.0, (-1) / ((2 * M_PI * frequency) * (m_value)));
    }

    Inductance Inductance::operator+(const Inductance &other) const{
        return Inductance(this->m_value + other.m_value, this->getEndpoints()[0], this->getEndpoints()[1]);
    }

    Inductance& Inductance::operator+=(const Inductance &other){
        this->m_value += other.m_value;
        return *this;
    }

    Inductance Inductance::operator||(const Inductance &other) const {
        return Inductance((this->m_value * other.m_value)/(this->m_value + other.m_value),
                            this->getEndpoints()[0], this->getEndpoints()[1]);
    }

    Inductance& Inductance::operator|=(const Inductance &other){
        this->m_value = ((this->m_value*other.m_value)/(this->m_value + other.m_value));
        return *this;
    }

}