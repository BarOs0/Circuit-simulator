#include "Elements.hpp"

int main(){

    IndependantV V1(10, 1, 0);
    Resistance R1(10, 1, 2);
    Capacitance C1(60e-9, 2, 0);
    Resistance R2(10, 2, 3);
    Capacitance C2(120e-9, 3, 0);
    Resistance R3(10, 3, 0);

    std::vector<Element*> elements{&V1, &R1, &C1, &R2, &C2, &R3};

    Circuit c1(elements, 1e-3);

    std::cout << R2.isNeighbour(C2, 3) << std::endl;
    std::cout << R2.isNeighbour(C2) << std::endl;

    std::cout << V1.isNeighbour(R3) << std::endl;
}