#include "IndependantJ.hpp"

namespace bo{

    IndependantJ::IndependantJ(std::complex<double> j, unsigned int pnode, unsigned int nnode)
                                : Active(j, pnode, nnode, 'J'){}

}