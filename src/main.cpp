#include "Resistance.hpp"
#include "Capacitance.hpp"
#include "Inductance.hpp"
#include "IndependantV.hpp"
#include "IndependantJ.hpp"
#include "Circuit.hpp"

int main(){

    bo::IndependantV Us(std::complex<double>(0.5, 0), 1, 0);
    bo::Resistance Rs(50, 1, 2);
    bo::Capacitance C22(100e-9, 2, 3);
    bo::Capacitance C21(47e-9, 3, 4);
    bo::Resistance R21(1000, 4, 0);
    bo::Resistance R22(1000, 4, 5);
    bo::Inductance L21(10e-3, 3, 5);
    bo::Capacitance C23(100e-9, 5, 0);

    std::vector<bo::Element*> elements{&Us, &Rs, &C22, &C21, &R21, &R22, &L21, &C23};

    bo::Circuit c1(elements, 1000);

    c1.displayPotentials();
    c1.displayCurrents();
    
}