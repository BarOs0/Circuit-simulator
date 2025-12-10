#include "Passive.hpp"

namespace bo{

    Passive::Passive(double val, unsigned int pnode, unsigned int nnode, char type)
                    : Element(pnode, nnode, type), m_passive_value(validateVal(val)){}

    double Passive::getPassiveValue() const {return m_passive_value;}

    void Passive::setPassiveValue(double val){
        m_passive_value = validateVal(val);
    }

    double Passive::validateVal(double val){
        if(val < E_LIM){
            throw std::invalid_argument("Value of the passive element must be positive! Invalid value: "
                    + std::to_string(val));
        }
        return val;
    }

}