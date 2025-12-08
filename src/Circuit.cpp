#include "Circuit.hpp"

#define Y_DET_LIM 1e-14 // for floating node detection

Circuit::Circuit(const std::vector<Element*> &elements, double frequency)
                : m_frequency(validateFrequency(frequency)){

    buildCircuit(elements);

    m_passives.insert(m_passives.end(), m_resistors.begin(), m_resistors.end());
    m_passives.insert(m_passives.end(), m_capacitors.begin(), m_capacitors.end());
    m_passives.insert(m_passives.end(), m_inductors.begin(), m_inductors.end());

    m_actives.insert(m_actives.end(), m_vsources.begin(), m_vsources.end());
    m_actives.insert(m_actives.end(), m_jsources.begin(), m_jsources.end());

    m_total_vsources = m_vsources.size();
    m_total_jsources = m_jsources.size();

    solve();
}

double Circuit::getFrequency() const {return m_frequency;}

void Circuit::setFrequency(double frequency){m_frequency = validateFrequency(frequency);}

unsigned int Circuit::getTotalNodes() const {return m_total_nodes;}

unsigned int Circuit::getTotalVsources() const {return m_total_vsources;}

unsigned int Circuit::getTotalJsources() const {return m_total_jsources;}

std::vector<std::complex<double>> Circuit::getPotentials() const {return m_v;}

std::vector<std::complex<double>> Circuit::getCurrents() const {return m_j;}

void Circuit::displayPotentials() const {
    std::cout << "============ POTENTIALS[V] ============" << std::endl;
    for(unsigned int i = 0; i < m_v.size(); i++){
        std::cout << "Node " << (i + 1) << " Potential: " << 
        std::to_string(m_v[i].real()) << ((m_v[i].imag()) > 0 ? "+" : "") << m_v[i].imag() << "i" << std::endl;
    }
    std::cout << "=====================================" << std::endl;
}

void Circuit::displayCurrents() const {
    std::cout << std::endl;
    std::cout << "============ CURRENTS[A] ============" << std::endl;
    for(unsigned int i = 0; i < m_j.size(); i++){
        std::cout << "V" << (i + 1) << " Current: " << 
        std::to_string(m_j[i].real()) << ((m_j[i].imag()) > 0 ? "+" : "") << m_j[i].imag() << "i" << std::endl;
    }
    std::cout << "=====================================" << std::endl;
}

void Circuit::buildCircuit(const std::vector<Element*> &elements){
    
       std::array<unsigned int, 2> nodes_max = {0, 0};

        for(auto e : elements){

            //looking for total number of nodes
            std::array<unsigned int, 2> nodes = e->getEndpoints();
        
            nodes_max[0] = std::max(nodes_max[0], nodes[0]);
            nodes_max[1] = std::max(nodes_max[1], nodes[1]);

            //parsing
            switch (e->whoAmI())
            {
            case 'R':
                m_resistors.push_back(dynamic_cast<Resistance*>(e));
                break;
            case 'C':
                m_capacitors.push_back(dynamic_cast<Capacitance*>(e));
                break;
            case 'L':
                m_inductors.push_back(dynamic_cast<Inductance*>(e));
                break;
            case 'V':
                m_vsources.push_back(dynamic_cast<IndependantV*>(e));
                break;
            case 'J':
                m_jsources.push_back(dynamic_cast<IndependantJ*>(e));
                break;
            default:
                throw std::invalid_argument("Invalid component name: "
                     + std::string(1, e->whoAmI())
                     + std::to_string(e->getId()));
            }
        }

        m_total_nodes = std::max(nodes_max[0], nodes_max[1]); // total number of nodes
}

void Circuit::generate_A(){

    unsigned int size = m_total_nodes + m_total_vsources;
    
    m_A.resize(size, size);
    m_A.setZero();

    generate_Y();
    generate_B();
    generate_C();
    generate_D();

    for(unsigned int i = 0; i < m_total_nodes; i++){
        for(unsigned int j = 0; j < m_total_nodes; j++){
            m_A(i, j) = m_Y(i, j);
        }
    }

    for(unsigned int i = 0; i < m_total_nodes; i++){
        for(unsigned int j = 0; j < m_total_vsources; j++){
            m_A(i, m_total_nodes + j) = m_B[i][j];
        }
    }

    for(unsigned int i = 0; i < m_total_vsources; i++){
        for(unsigned int j = 0; j < m_total_nodes; j++){
            m_A(m_total_nodes + i, j) = m_C[i][j];
        }
    }

    for(unsigned int i = 0; i < m_total_vsources; i++){
        for(unsigned int j = 0; j < m_total_vsources; j++){
            m_A(m_total_nodes + i, m_total_nodes + j) = m_D[i][j];
        }
    }
}

void Circuit::generate_Y(){

    m_Y.resize(m_total_nodes, m_total_nodes);
    m_Y.setZero();

    std::complex<double> y(0.0,0.0);

    for(auto p : m_passives){

        y = p->getAdmitance(m_frequency);

        unsigned int pnode = p->getEndpoints()[0];
        unsigned int nnode = p->getEndpoints()[1];

        if(pnode != 0){
            m_Y(pnode - 1, pnode - 1) += y;
            if(nnode != 0){
                m_Y(pnode - 1, nnode - 1) -= y;
            }
        }

        if(nnode != 0){
            m_Y(nnode - 1, nnode - 1) += y;
            if(pnode != 0){
                m_Y(nnode - 1, pnode - 1) -= y;
            }
        }
    }

    if(std::abs(m_Y.determinant()) < Y_DET_LIM){
        throw std::invalid_argument("Your topology has floating nodes! Please check the wires.");
    }
}

void Circuit::generate_B(){

    m_B.resize(m_total_nodes, std::vector<std::complex<double>>(m_total_vsources,
                std::complex<double>(0.0, 0.0)));

    for(auto v : m_vsources){

        unsigned int pnode = v->getEndpoints()[0];
        unsigned int nnode = v->getEndpoints()[1];
        
        if(pnode != 0){
            m_B[pnode - 1][v->getId() - 1] = std::complex<double>(1.0, 0);
        }
        if(nnode != 0){
            m_B[nnode - 1][v->getId() - 1] = std::complex<double>(-1.0, 0);
        }
    }
}

void Circuit::generate_C(){

    m_C.resize(m_total_vsources, std::vector<std::complex<double>>(m_total_nodes,
                std::complex<double>(0.0, 0.0)));

    for(auto v : m_vsources){

        unsigned int pnode = v->getEndpoints()[0];
        unsigned int nnode = v->getEndpoints()[1];
        
        if(pnode != 0){
            m_C[v->getId() - 1][pnode - 1] = std::complex<double>(1.0, 0);
        }
        if(nnode != 0){
            m_C[v->getId() - 1][nnode - 1] = std::complex<double>(-1.0, 0);
        }
    }
}

void Circuit::generate_D(){

    m_D.resize(m_total_vsources, std::vector<std::complex<double>>(m_total_vsources,
            std::complex<double>(0.0, 0.0)));
}

void Circuit::generate_z(){

    unsigned int size = m_total_nodes + m_total_vsources;
    
    m_z.resize(size);
    m_z.setZero();

    for(auto j : m_jsources){

        unsigned int pnode = j->getEndpoints()[0];
        unsigned int nnode = j->getEndpoints()[1];

        if(pnode != 0){
            m_z(pnode - 1) += j->getSourceValue();
        }
        if(nnode != 0){
            m_z(nnode - 1) -= j->getSourceValue();
        }
    }

    for(auto v : m_vsources){
        m_z(m_total_nodes + v->getId() - 1) = v->getSourceValue();
    }
}

void Circuit::solve(){

    generate_A();
    generate_z();

    Eigen::VectorXcd x = m_A.colPivHouseholderQr().solve(m_z);

    m_v.resize(m_total_nodes);
    std::copy(x.data(), x.data() + m_total_nodes, m_v.begin());

    m_j.resize(m_total_vsources);
    std::copy(x.data() + m_total_nodes, x.data() + m_total_nodes + m_total_vsources, m_j.begin());
}

double Circuit::validateFrequency(double frequency){
    if(frequency < F_LIM){
        throw std::invalid_argument("Frequency cannot be negative or zero! Invalid frequency: "
                + std::to_string(frequency));
    }
    return frequency;
}