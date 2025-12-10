#include "Resistance.hpp"
#include "Capacitance.hpp"
#include "Inductance.hpp"
#include "IndependantV.hpp"
#include "IndependantJ.hpp"
#include "Circuit.hpp"

int main(){

    bo::IndependantV Uwe(std::complex<double>(1,0), 1, 0);
    bo::Resistance R1(1e-3, 1, 2);
    bo::Capacitance C1(1e-6, 2, 0);

    std::cout << R1.getId() << std::endl;

    std::vector<bo::Element*> elements{&Uwe, &R1, &C1};

    bo::Circuit c1(elements, 1000);
    bo::Circuit c2(elements, 10000);
    bo::Circuit c3(elements, 10000000);

    c1.solve();
    c2.solve();
    c3.solve();

    c1.displayPotentials();
    c1.displayCurrents();
    std::cout << std::endl;

    c2.displayPotentials();
    c2.displayCurrents();
    std::cout << std::endl;

    c3.displayPotentials();
    c3.displayCurrents();
    std::cout << std::endl;
}