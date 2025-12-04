#pragma once

#include "Element.hpp"

#define F_LIM 1e-12

class Circuit{

    public:

        Circuit(const std::vector<Element*> &elements, double frequnecy);

        double getFrequnecy() const;

        void setFrequency(double frequency);

        unsigned int getTotalNodes() const;

        unsigned int getTotalVsources() const;

        unsigned int getTotalJsources() const;

    private:

        std::vector<Element*> m_resistors, m_capacitors, m_inductors, m_vsources, m_components, m_jsources;

        std::vector<std::vector<std::complex<double>>> m_A, m_G, m_B, m_C, m_D;

        unsigned int m_total_nodes{0}; // n

        unsigned int m_total_vsources{0}, m_total_jsources{0}; // m

        double m_frequency;

        void buildCircuit(const std::vector<Element*> &elements);

        static double validateFrequency(double frequency);
};