#include <iostream>

#include "Resistance.hpp"
#include "Capacitance.hpp"
#include "Inductance.hpp"
#include "IndependantV.hpp"
#include "IndependantJ.hpp"
#include "Circuit.hpp"

int main(){
    IndependantV V1(std::complex<double>(10.0, 1), 1, 0);
    Resistance R1(10, 1, 2);
    Capacitance C1(60e-9, 2, 0);
    Resistance R2(10, 2, 3);
    Capacitance C2(120e-9, 3, 0);
    Resistance R3(10, 3, 0);
    IndependantJ J1(std::complex<double>(1.0, 0),1,2);

    std::vector<Element*> elements{&V1, &R1, &C1, &R2, &C2, &R3, &J1};

    Circuit c1(elements, 1e-3);

    std::cout << R2.isNeighbour(C2, 3) << std::endl;
    std::cout << R2.isNeighbour(C2) << std::endl;

    std::cout << V1.isNeighbour(R3) << std::endl;

    std::cout << V1.whoAmI() << V1.getId() << std::endl;
    std::cout << R1.whoAmI() << R1.getId() << std::endl;
    std::cout << R2.whoAmI() << R2.getId() << std::endl;
    std::cout << R3.whoAmI() << R3.getId() << std::endl;
    std::cout << C2.whoAmI() << C2.getId() << std::endl;

    std::cout << J1.isNeighbour(R3) << std::endl;
    std::cout << J1.isNeighbour(R2,2) << std::endl;
    std::cout << J1.whoAmI() << J1.getId() << std::endl;

    Element* e = new IndependantJ(1,1,0);
    delete e;

    std::cout << c1.getTotalNodes() << std::endl;
    std::cout << c1.getTotalVsources() << std::endl;
    std::cout << c1.getTotalJsources() << std::endl;
}