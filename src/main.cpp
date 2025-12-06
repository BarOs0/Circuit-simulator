#include <iostream>

#include "Resistance.hpp"
#include "Capacitance.hpp"
#include "Inductance.hpp"
#include "IndependantV.hpp"
#include "IndependantJ.hpp"
#include "Circuit.hpp"

int main(){
   
    IndependantV V1(std::complex<double>(sqrt(2), 0), 1, 0);
    Resistance R1(1, 1, 2);
    Capacitance C1(25, 2, 0);
    Inductance L1(1, 2, 3);
    Resistance R2(1, 3, 0);

    std::vector<Element*> elements{&V1, &R1, &C1, &L1, &R2};

    Circuit c1(elements, 0.2);

    std::vector<std::complex<double>> v = c1.getPotentials();
    std::vector<std::complex<double>> c = c1.getCurrents();

    std::cout << "POTENTIALS: " << std::endl;

    for(unsigned int i = 0; i < v.size(); i++){
        std::cout << (i + 1) << ". " << std::to_string(v[i].real()) << std::to_string(v[i].imag()) << std::endl;
    }

    std::cout << "CURRENTS: " << std::endl;

    for(unsigned int i = 0; i < v.size(); i++){
        std::cout << (i + 1) << ". " << std::to_string(c[i].real()) << std::to_string(c[i].imag()) << std::endl;
    }
}