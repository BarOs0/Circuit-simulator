#include "Capacitance.hpp"

namespace bo{
    
    Capacitance::Capacitance(double c, unsigned int pnode, unsigned int nnode)
                        : Passive(c, pnode, nnode, 'C'){}

    std::complex<double> Capacitance::getAdmittance(double frequency) const {
        return std::complex<double>(0.0, (2 * M_PI * frequency) * (getPassiveValue()));
    }

    Capacitance Capacitance::operator+(const Capacitance &other) const {
        return Capacitance((this->getPassiveValue() * other.getPassiveValue())/
                            (this->getPassiveValue() + other.getPassiveValue()),
                            this->getEndpoints()[0], this->getEndpoints()[1]);
    }

    Capacitance& Capacitance::operator+=(const Capacitance &other){
        setPassiveValue((this->getPassiveValue()*other.getPassiveValue())/
                        (this->getPassiveValue() + other.getPassiveValue()));
        return *this;
    }

    Capacitance Capacitance::operator||(const Capacitance &other) const{
        return Capacitance(this->getPassiveValue() + other.getPassiveValue(), 
                            this->getEndpoints()[0], this->getEndpoints()[1]);
    }

    Capacitance& Capacitance::operator|=(const Capacitance &other){
        setPassiveValue(this->getPassiveValue() + other.getPassiveValue());
        return *this;
    }

}