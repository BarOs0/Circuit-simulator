#include "IndependentJ.hpp"

namespace bo{

    IndependentJ::IndependentJ(std::complex<double> j, unsigned int pnode, unsigned int nnode)
                                : Active(j, pnode, nnode, 'J'){}

}