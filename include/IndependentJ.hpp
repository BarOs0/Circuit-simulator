#pragma once

#include "Active.hpp"

namespace bo{

    /**
     * @brief Derived class for independent current sources
     * 
     * IndependentJ represents an independent current source component.
     */
    class IndependentJ : public Active{

        public:

            /**
             * @brief Public constructor for user (main())
             * @param j Current source EFFECTIVE value (complex) [A]
             * @param pnode Positive node number
             * @param nnode Negative node number
             */
            IndependentJ(std::complex<double> j, unsigned int pnode, unsigned int nnode);
    };

}