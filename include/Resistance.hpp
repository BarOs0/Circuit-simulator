#pragma once

#include "Passive.hpp"

namespace bo{

    /**
     * @brief Derived class for resistors
     * 
     * Resistance represents a resistor component.
     * Contains features related to resistors.
     */
    class Resistance : public Passive{

        public:

            /**
             * @brief Public constructor for user (main())
             * @param r Resistance value [Ohms]
             * @param pnode Positive node number
             * @param nnode Negative node number
             * @throw std::invalid_argument if r < E_LIM
             */
            Resistance(double r, unsigned int pnode, unsigned int nnode);

            /**
             * @brief Calculates frequency-independent admittance
             * @param frequency Operating frequency [Hz] (unused for resistors)
             * @return Complex admittance (conductance G = 1/R)
             */
            std::complex<double> getAdmittance(double frequency) const override;

            /**
             * @brief Overloaded operator + for series connection
             * @param other Resistor to connect in series
             * @return New Resistance with total value
             */
            Resistance operator+(const Resistance &other) const;

            /**
             * @brief Overloaded operator += for series connection
             * @param other Resistor to connect in series
             * @return Reference to this Resistance with updated value
             */
            Resistance& operator+=(const Resistance &other);

            /**
             * @brief Overloaded operator || for parallel connection
             * @param other Resistor to connect in parallel
             * @return New Resistance with total value
             */
            Resistance operator||(const Resistance &other) const;

            /**
             * @brief Overloaded operator |= for parallel connection
             * @param other Resistor to connect in parallel
             * @return Reference to this Resistance with updated value
             */
            Resistance& operator|=(const Resistance &other);
    };

}