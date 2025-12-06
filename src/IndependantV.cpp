#include "IndependantV.hpp"

IndependantV::IndependantV(std::complex<double> v, unsigned int pnode, unsigned int nnode)
                            : Active(v, pnode, nnode, 'V'){}