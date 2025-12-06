#pragma once

#include "Element.hpp"

class Active : public Element{

    public:

        std::complex<double> getSourceValue() const;

    protected:

        Active(std::complex<double> val, unsigned int pnode, unsigned int nnode, char type);

    private:

        std::complex<double> m_source_value;
};