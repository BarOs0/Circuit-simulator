#pragma once

#include <iostream>
#include <Eigen/Dense>

#include "Element.hpp"
#include "Passive.hpp"
#include "Active.hpp"
#include "Resistance.hpp"
#include "Capacitance.hpp"
#include "Inductance.hpp"
#include "IndependantV.hpp"
#include "IndependantJ.hpp"

#define F_LIM 1e-12

class Circuit{

    public:

        Circuit(const std::vector<Element*> &elements, double frequency);

        double getFrequency() const;

        void setFrequency(double frequency);

        unsigned int getTotalNodes() const;

        unsigned int getTotalVsources() const;

        unsigned int getTotalJsources() const;

        std::vector<std::complex<double>> getPotentials() const;

        std::vector<std::complex<double>> getCurrents() const;

        void displayPotentials() const;

        void displayCurrents() const;

    private:

        std::vector<Resistance*> m_resistors;
        std::vector<Capacitance*> m_capacitors;
        std::vector<Inductance*> m_inductors;

        std::vector<IndependantV*> m_vsources;
        std::vector<IndependantJ*> m_jsources;

        std::vector<Passive*> m_passives;
        std::vector<Active*> m_actives;

        std::vector<std::vector<std::complex<double>>> m_B, m_C, m_D;

        Eigen::MatrixXcd m_A;
        Eigen::MatrixXcd m_Y;
        Eigen::VectorXcd m_z;

        std::vector<std::complex<double>> m_v;
        std::vector<std::complex<double>> m_j;
        
        unsigned int m_total_nodes{0}; // n

        unsigned int m_total_vsources{0}, m_total_jsources{0}; // m

        double m_frequency;

        void buildCircuit(const std::vector<Element*> &elements);

        void generate_A();

        void generate_Y();

        void generate_B();

        void generate_C();

        void generate_D();

        void generate_z();

        void solve();

        static double validateFrequency(double frequency);
};