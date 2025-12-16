#include "IndependentV.hpp"

namespace bo{

    IndependentV::IndependentV(std::complex<double> v, unsigned int pnode, unsigned int nnode)
                                : Active(v, pnode, nnode, 'V'){}

}