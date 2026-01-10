#pragma once

#include "Element.hpp"

namespace bo{

    /**
     * @brief Derived class for active elements in circuit theory
     * 
     * Active represents an electronic component:
     * - Independent voltage source
     * - Independent current source
     * 
     * Contains information about active element values.
     */

    class Active : public Element{

        public:

            /**
             * @brief Returns value of active element
             * @return Active element value (complex) [V/A]
             */
            std::complex<double> getActiveValue() const;

            /**
             * @brief Sets new active element value (complex) [V/A]
             * @param val New complex value
             */
            void setActiveValue(const std::complex<double> &val);

        protected:

            /**
             * @brief Protected constructor for derived classes
             * @param val Active element value (complex) [V/A]
             * @param pnode Positive node number
             * @param nnode Negative node number
             * @param type Active element type character ('V', 'J')
             */
            Active(std::complex<double> val, unsigned int pnode, unsigned int nnode, char type);

        private:

            std::complex<double> m_active_value; ///< Active element value (complex) [V/A]
    };
    
}