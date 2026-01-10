/**
 * Example usage of the Circuit-simulator library.
 * Defines a simple RC circuit and solves it for different frequencies.
 * 
 *    node 1   R1    node 2   R2    node 3
 *       +---[    ]----+----[    ]---+
 *       |                           |
 * Uwe ( ^ )                       __|__ C1
 *     ( | )                       _____
 *       |                           |
 *      =_= node 0                  =_= node 0
 * 
 * NOTE: Nodes should be numbered consecutively, starting with 1. Number 0 is reserved for the ground node.
 */

#include "Resistance.hpp" // <- Include necessary modules
#include "Capacitance.hpp"
//#include "Inductance.hpp"
#include "IndependentV.hpp"
//#include "IndependentJ.hpp"
#include "Circuit.hpp"

int main(){

    // Step 1: Create your netlist
    bo::IndependentV Uwe(std::complex<double>(1,0), 1, 0); // sources must be initialized with an EFFECTIVE value
    bo::Resistance R1(500, 1, 2);
    bo::Resistance R2(500, 2, 3);
    bo::Capacitance C1(1e-6, 3, 0);

    // (Optional) Calculate total value for series and parallel connections (not dependent on netlist, use as calculator)
    std::cout << "R1 + R2 (series): " << (R1 + R2).getPassiveValue() << "Ω" << std::endl;
    std::cout << "R1 || R2 (parallel): " << (R1 || R2).getPassiveValue() << "Ω" << std::endl;

    //(Optional) You can change element values
    // R1 += R2;
    // std::cout << "R1 += R2 (series): " << R1.getPassiveValue() << "Ω" << std::endl;
    // R1 |= R2;
    // std::cout << "R1 |= R2 (parallel): " << R1.getPassiveValue() << "Ω" << std::endl;
    
    // (Optional) You can get information about elements - see doxygen documentation for details
    std::cout<< "R1 ID: " << R1.getId() << std::endl;
    std::cout<< "R1 nodes: " << R1.getEndpoints()[0] << ", " << R1.getEndpoints()[1] << std::endl;
    std::cout<< "R1 is connected to R2? " << (R1.isNeighbour(R2) ? "true" : "false" )<< std::endl;
    std::cout<< "R1 is connected to R2 at node 2? " << (R1.isNeighbour(R2,2) ? "true" : "false" )<< std::endl;
    std::cout<< "R1 = " << R1.getPassiveValue() << "Ω" << std::endl;
    std::cout<< "C1 complex admittance for 100Hz: " << C1.getAdmittance(100).real() << 
    (C1.getAdmittance(100).imag() >= 0 ? "+" : "") << C1.getAdmittance(100).imag() << "i" << std::endl;
    std::cout << "C1 type: " << C1.whoAmI() << std::endl;
    
    std::cout<< "Uwe complex value: " << Uwe.getActiveValue().real() << 
    (Uwe.getActiveValue().imag() >= 0 ? "+" : "") << Uwe.getActiveValue().imag() << "i" << std::endl;

    // (Optional) You can set different values for elements - see doxygen documentation for details
    // R1.setPassiveValue(3000);
    // R1.setEndpoints(2,3); // <- Be careful with floating nodes :)
    // R2.setEndpoints(1,2);
    // Uwe.setActiveValue(std::complex<double>(1, 1));

    // Step 2: Pack your netlist into a vector
    std::vector<bo::Element*> elements{&Uwe, &R1, &R2, &C1};

    // Step 3: Define circuit for fixed frequency [Hz]
    bo::Circuit O1(elements, 10);
    bo::Circuit O2(elements, 100);
    bo::Circuit O3(elements, 1000);

    // Step 4: Solve the circuits
    O1.solve();
    O2.solve();
    O3.solve();

    // Step 5: Display results
    O1.displayPotentials();
    O1.displayCurrents();

    O2.displayPotentials();
    O2.displayCurrents();

    O3.displayPotentials();
    O3.displayCurrents();
}