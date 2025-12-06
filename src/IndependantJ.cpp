#include "IndependantJ.hpp"

IndependantJ::IndependantJ(std::complex<double> j, unsigned int pnode, unsigned int nnode)
                            : Active(j, pnode, nnode, 'J'){}