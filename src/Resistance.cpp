#include "Resistance.hpp"

namespace bo{

    Resistance::Resistance(double r, unsigned int pnode, unsigned int nnode)
                        : Passive(r, pnode, nnode, 'R'){}

    std::complex<double> Resistance::getAdmitance(double) const {
        return std::complex<double>((1 / (m_value)), 0.0);
    }

    Resistance Resistance::operator+(const Resistance &other) const{
        return Resistance(this->m_value + other.m_value, this->getEndpoints()[0], this->getEndpoints()[1]);
    }

    Resistance& Resistance::operator+=(const Resistance &other){
        this->m_value += other.m_value;
        return *this;
    }

    Resistance Resistance::operator||(const Resistance &other) const {
        return Resistance((this->m_value * other.m_value)/(this->m_value + other.m_value),
                            this->getEndpoints()[0], this->getEndpoints()[1]);
    }

    Resistance& Resistance::operator|=(const Resistance &other){
        this->m_value = ((this->m_value*other.m_value)/(this->m_value + other.m_value));
        return *this;
    }

}