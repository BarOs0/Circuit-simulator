#pragma once

#include <iostream>
#include <Eigen/Dense>

#include "Element.hpp"
#include "Passive.hpp"
#include "Active.hpp"
#include "Resistance.hpp"
#include "Capacitance.hpp"
#include "Inductance.hpp"
#include "IndependentV.hpp"
#include "IndependentJ.hpp"

namespace bo{

    /// Epsilon limit for frequency value validation
    constexpr double F_LIM = 1e-12;

    /// Epsilon limit for Y matrix determinant (checks for floating nodes and must VERY low)
    constexpr double Y_DET_LIM = 1e-18;

    /**
     * @brief Main class for circuit analysis
     * 
     * Circuit performs nodal analysis using Modified Nodal Analysis (MNA) method.
     * Solves for node potentials and voltage sources branches currents in frequency domain.
     */
    class Circuit{

        public:

            /**
             * @brief Public constructor for circuit creation in main()
             * @param elements Vector of pointers to circuit elements
             * @param frequency Operating frequency [Hz]
             * @throw std::invalid_argument if frequency < F_LIM
             */
            Circuit(const std::vector<Element*> &elements, double frequency);

            /**
             * @brief Returns operating frequency
             * @return Operating frequency [Hz]
             */
            double getFrequency() const;

             /**
             * @brief Returns total number of nodes (excluding GND)
             * @return Number of nodes
             */
            unsigned int getTotalNodes() const;

             /**
             * @brief Returns total number of independent voltage sources
             * @return Number of voltage sources
             */
            unsigned int getTotalVsources() const;

            /**
             * @brief Returns total number of independent current sources
             * @return Number of current sources
             */
            unsigned int getTotalJsources() const;

            /**
             * @brief Returns node potentials vector
             * @return Complex potentials at each node [V]
             */
            std::vector<std::complex<double>> getPotentials() const;

             /**
             * @brief Returns currents through voltage sources vector
             * @return Complex currents through voltage sources [A]
             */
            std::vector<std::complex<double>> getCurrents() const;

             /**
             * @brief Displays node potentials in formatted output
             */
            void displayPotentials() const;

             /**
             * @brief Displays voltage source currents in formatted output
             */
            void displayCurrents() const;

             /**
             * @brief Solves the MNA system Ax = z
             */
            void solve();

        private:

            std::vector<Resistance*> m_resistors;    ///< Vector of resistor pointers
            std::vector<Capacitance*> m_capacitors;  ///< Vector of capacitor pointers
            std::vector<Inductance*> m_inductors;    ///< Vector of inductor pointers

            std::vector<IndependentV*> m_vsources;   ///< Vector of voltage source pointers
            std::vector<IndependentJ*> m_jsources;   ///< Vector of current source pointers

            std::vector<Passive*> m_passives;        ///< Combined vector of passive elements
            std::vector<Active*> m_actives;          ///< Combined vector of active elements

            std::vector<std::vector<std::complex<double>>> m_B;  ///< Incidence matrix for voltage sources
            std::vector<std::vector<std::complex<double>>> m_C;  ///< Transpose of B matrix
            std::vector<std::vector<std::complex<double>>> m_D;  ///< Zero matrix for MNA

            Eigen::MatrixXcd m_A;  ///< System matrix [Y B; C D]
            Eigen::MatrixXcd m_Y;  ///< Nodal admittance matrix
            Eigen::VectorXcd m_z;  ///< Right-hand side vector [j; v]

            std::vector<std::complex<double>> m_v;  ///< Node potentials solution vector [V]
            std::vector<std::complex<double>> m_j;  ///< Voltage source currents solution vector [A]
            
            unsigned int m_total_nodes{0};     ///< Total number of nodes (n)
            unsigned int m_total_vsources{0};  ///< Total number of voltage sources (m)
            unsigned int m_total_jsources{0};  ///< Total number of current sources 

            double m_frequency;  ///< Operating frequency [Hz]

            inline static unsigned int c_counter = 1; ///< Circuit counter

            unsigned int m_id; ///< Unique circuit ID

            /**
             * @brief Parse circuit components from element vector
             *        Calculates number on nodes (maxiumum seeking)
             * @param elements Vector of circuit elements
             */
            void buildCircuit(const std::vector<Element*> &elements);

             /**
             * @brief Generates system matrix A = [Y, B; C, D]
             */
            void generate_A();

            /**
             * @brief Generates nodal admittance matrix Y
             */
            void generate_Y();

            /**
             * @brief Generates incidence matrix B for voltage sources
             */
            void generate_B();

            /**
             * @brief Generates transpose matrix C = B^T
             */
            void generate_C();

            /**
             * @brief Generates zero matrix D
             */
            void generate_D();

            /**
             * @brief Generates right-hand side vector z = [j; v]
             */
            void generate_z();

            /**
             * @brief Validates frequency value [Hz]
             * @param frequency Frequency to validate
             * @return Validated frequency
             * @throw std::invalid_argument if frequency < F_LIM
             */
            static double validateFrequency(double frequency);
    };

}