#include "Active.hpp"

namespace bo{

    Active::Active(std::complex<double> val, unsigned int pnode, unsigned int nnode, char type)
                : Element(pnode, nnode, type), m_active_value(val){}

    std::complex<double> Active::getActiveValue() const {return m_active_value;}

    void Active::setActiveValue(const std::complex<double> &val){
        m_active_value = val;
    }
}