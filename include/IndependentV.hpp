#pragma once

#include "Active.hpp"

namespace bo{

    /**
     * @brief Derived class for independent voltage sources
     * 
     * IndependentV represents an independent voltage source component.
     */
    class IndependentV : public Active{

        public:

            /**
             * @brief Public constructor for user (main())
             * @param v Voltage source value (complex) [V]
             * @param pnode Positive node number
             * @param nnode Negative node number
             */
            IndependentV(std::complex<double> v, unsigned int pnode, unsigned int nnode);
    };

}