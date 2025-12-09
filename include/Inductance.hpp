#pragma once

#include "Passive.hpp"

namespace bo{

    /**
     * @brief Derived class for inductors
     * 
     * Inductance represents an inductor component. 
     * Contains features related to inductors.
     */
    class Inductance : public Passive{

        public:

            /**
             * @brief Public constructor for user (main())
             * @param l Inductance value [Henrys]
             * @param pnode Positive node number
             * @param nnode Negative node number
             * @throw std::invalid_argument if l < E_LIM
             */
            Inductance(double l, unsigned int pnode, unsigned int nnode);

            /**
             * @brief Calculates frequency-dependent admittance
             * @param frequency Operating frequency [Hz]
             * @return Complex admittance (susceptance B = 1/(jωL))
             */
            std::complex<double> getAdmittance(double frequency) const override;

            /**
             * @brief Overloaded operator + for series connection
             * @param other Inductor to connect in series
             * @return New Inductance with total value
             */
            Inductance operator+(const Inductance &other) const;

            /**
             * @brief Overloaded operator += for series connection
             * @param other Inductor to connect in series
             * @return Reference to this Inductance with updated value
             */
            Inductance& operator+=(const Inductance &other);

            /**
             * @brief Overloaded operator || for parallel connection
             * @param other Inductor to connect in parallel
             * @return New Inductance with total value
             */
            Inductance operator||(const Inductance &other) const;

            /**
             * @brief Overloaded operator |= for parallel connection
             * @param other Inductor to connect in parallel
             * @return Reference to this Inductance with updated value
             */
            Inductance& operator|=(const Inductance &other);
    };

}