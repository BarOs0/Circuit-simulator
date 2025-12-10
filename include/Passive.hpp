#pragma once

#include "Element.hpp"

namespace bo{

    /// Epsilon limit for element value
    constexpr double E_LIM = 1e-12; 

    /**
     * @brief Derived class for passive elements in circuit theory
     * 
     * Passive represents an electronic component:
     * - Resistance
     * - Capacitance
     * - Inductance
     * 
     * Contains information about passive element values.
     * Calulates complex admittance.
     */
    class Passive : public Element{

        public: 

            /**
             * @brief Returns value of passive element
             * @return Passive element value [Ohms/Farads/Henrys]
             */
            double getPassiveValue() const;

            /**
             * @brief Sets new passive element value [Ohms/Farads/Henrys]
             * @param val New value
             * @throw std::invalid_argument if val < E_LIM
             */
            void setPassiveValue(double val);

            /**
             * @brief Returns frequency-(in)dependent admittance
             * @param frequency Operating frequency [Hz]
             * @return Complex admittance for the given frequency
             */
            virtual std::complex<double> getAdmittance(double frequency) const = 0;

            /**
             * @brief Virtual destructor for the Passive class
             */
            virtual ~Passive() = default;

        protected:

            /**
             * @brief Protected constructor for derived classes
             * @param val Passive element value [Ohms/Farads/Henrys]
             * @param pnode Positive node number
             * @param nnode Negative node number
             * @param type Passive element type character ('R', 'C', 'L')
             */
            Passive(double val, unsigned int pnode, unsigned int nnode, char type);

        private:

            double m_passive_value; ///< Passive element value

            /**
             * @brief Validates passive element value
             * @param val Value
             * @return Validated passive element value
             * @throw std::invalid_argument if val < E_LIM
             */
            static double validateVal(double val);
    };
    
}