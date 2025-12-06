#include "Active.hpp"

Active::Active(std::complex<double> val, unsigned int pnode, unsigned int nnode, char type)
            : Element(-1.0, pnode, nnode, type), m_source_value(val){}

std::complex<double> Active::getSourceValue() const {return m_source_value;}