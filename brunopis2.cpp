#include "Elements.hpp"

int main(){

    int pnode = 0;
    int nnode = 0;

    Resistance R1(1/4, 1, 0);
    Resistance R2(1/2, 1, 0);
    Resistance R3(1/5, 1, 0);

    Capacitance C1(200.0, 3, 0);
    Capacitance C2(200.0, 1, 0);

    Inductance L1(300.0, 1, 0);
    Inductance L2(300.0, 1, 0);
    Inductance L3(300.0, 1, 0);
    Inductance L4(300.0, 1, 0);

    IndependantV V1(400.0, 1, 0);

    // std::cout << "R1" << R1.whoAmI() << R1.getId() << std::endl;
    // std::cout << "R2" << R2.whoAmI() << R2.getId() << std::endl;
    // std::cout << "R3" << R3.whoAmI() << R3.getId() << std::endl;

    // std::cout << "C1" << C1.whoAmI() << C1.getId() << std::endl;
    // std::cout << "C2" << C2.whoAmI() << C2.getId() << std::endl;
    
    // std::cout << "L1" << L1.whoAmI() << L1.getId() << std::endl;
    // std::cout << "L2" << L2.whoAmI() << L2.getId() << std::endl;
    // std::cout << "L3" << L3.whoAmI() << L3.getId() << std::endl;
    // std::cout << "L4" << L4.whoAmI() << L4.getId() << std::endl;

    // std::cout << "V1" << V1.whoAmI() << V1.getId() << std::endl;

    // ===========================================================

    // std::cout << "R3.neighbourhood(C1)" << std::endl;
    // std::cout << R3.isNeighbour(C1,3) << std::endl;
    // std::cout << R3.isNeighbour(C1) << std::endl;

    // std::cout << "L1.neighbourhood(R3)" << std::endl;
    // std::cout << L1.isNeighbour(R3,3) << std::endl;
    // L1.getEndpoints(pnode, nnode);
    // std::cout << "L1: " << pnode << ", " << nnode << std::endl;
    // R3.getEndpoints(pnode, nnode);
    // std::cout << "R3: " << pnode  << ", " << nnode << std::endl;

    std::vector<Element*> elements{&R1, &R2, &R3};

    Circuit c1(elements, 10.0);

    std::cout << real(c1.same_node_sum(1)) << std::endl;


}