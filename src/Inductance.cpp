#include "Inductance.hpp"

namespace bo{

    Inductance::Inductance(double l, unsigned int pnode, unsigned int nnode)
                        : Passive(l, pnode, nnode, 'L'){}

    std::complex<double> Inductance::getAdmittance(double frequency) const {
        return std::complex<double>(0.0, (-1) / ((2 * M_PI * frequency) * (getPassiveValue())));
    }

    Inductance Inductance::operator+(const Inductance &other) const{
        return Inductance(this->getPassiveValue() + other.getPassiveValue(), 
                            this->getEndpoints()[0], this->getEndpoints()[1]);
    }

    Inductance& Inductance::operator+=(const Inductance &other){
        setPassiveValue(this->getPassiveValue() + other.getPassiveValue());
        return *this;
    }

    Inductance Inductance::operator||(const Inductance &other) const {
        return Inductance((this->getPassiveValue() * other.getPassiveValue())/
                            (this->getPassiveValue() + other.getPassiveValue()),
                            this->getEndpoints()[0], this->getEndpoints()[1]);
    }

    Inductance& Inductance::operator|=(const Inductance &other){
        setPassiveValue((this->getPassiveValue()*other.getPassiveValue())/
                        (this->getPassiveValue() + other.getPassiveValue()));
        return *this;
    }

}