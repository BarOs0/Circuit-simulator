#pragma once

#include "Passive.hpp"

namespace bo{

    /**
     * @brief Derived class for capacitors
     * 
     * Capacitance represents a capacitor component. 
     * Contains features related to capacitors.
     */
    class Capacitance : public Passive{

        public:

            /**
             * @brief Public constructor for user (main())
             * @param c Capacitance value [Farads]
             * @param pnode Positive node number
             * @param nnode Negative node number
             * @throw std::invalid_argument if c < E_LIM
             */
            Capacitance(double c, unsigned int pnode, unsigned int nnode);

            /**
             * @brief Calculates frequency-dependent admittance
             * @param frequency Operating frequency [Hz]
             * @return Complex admittance (susceptance B = jωC)
             */
            std::complex<double> getAdmittance(double frequency) const override;

            /**
             * @brief Overloaded operator + for series connection
             * @param other Capacitor to connect in series
             * @return New Capacitance with total value
             */
            Capacitance operator+(const Capacitance &other) const;

            /**
             * @brief Overloaded operator += for series connection
             * @param other Capacitor to connect in series
             * @return Reference to this Capacitance with updated value
             */
            Capacitance& operator+=(const Capacitance &other);

            /**
             * @brief Overloaded operator || for parallel connection
             * @param other Capacitor to connect in parallel
             * @return New Capacitance with total value
             */
            Capacitance operator||(const Capacitance &other) const;

            /**
             * @brief Overloaded operator |= for parallel connection
             * @param other Capacitor to connect in parallel
             * @return Reference to this Capacitance with updated value
             */
            Capacitance& operator|=(const Capacitance &other);
    };

}