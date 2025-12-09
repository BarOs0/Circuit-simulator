#include "Resistance.hpp"

namespace bo{

    Resistance::Resistance(double r, unsigned int pnode, unsigned int nnode)
                        : Passive(r, pnode, nnode, 'R'){}

    std::complex<double> Resistance::getAdmittance(double) const {
        return std::complex<double>((1.0 / (getPassiveValue())), 0.0);
    }

    Resistance Resistance::operator+(const Resistance &other) const{
        return Resistance(this->getPassiveValue() + other.getPassiveValue(), 
                        this->getEndpoints()[0], this->getEndpoints()[1]);
    }

    Resistance& Resistance::operator+=(const Resistance &other){
        setPassiveValue(this->getPassiveValue() + other.getPassiveValue());
        return *this;
    }

    Resistance Resistance::operator||(const Resistance &other) const {
        return Resistance((this->getPassiveValue() * other.getPassiveValue())/
                        (this->getPassiveValue() + other.getPassiveValue()),
                        this->getEndpoints()[0], this->getEndpoints()[1]);
    }

    Resistance& Resistance::operator|=(const Resistance &other){
        setPassiveValue(((this->getPassiveValue()*other.getPassiveValue())/
                        (this->getPassiveValue() + other.getPassiveValue())));
        return *this;
    }

}