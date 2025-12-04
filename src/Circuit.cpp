#include "Circuit.hpp"

Circuit::Circuit(const std::vector<Element*> &elements, double frequency)
                : m_components(elements), m_frequency(validateFrequency(frequency)){

    buildCircuit(elements);
}

double Circuit::getFrequnecy() const {return m_frequency;}

void Circuit::setFrequency(double frequency){m_frequency = validateFrequency(frequency);}

void Circuit::buildCircuit(const std::vector<Element*> &elements){
    
        unsigned int pnode_max = 0;
        unsigned int nnode_max = 0;
        unsigned int pnode = 0;
        unsigned int nnode = 0;

        for(auto e : elements){

            //looking for total number of nodes
            e->getEndpoints(pnode, nnode);
            if(pnode > pnode_max){
                pnode_max = pnode;
            }
            else if(nnode > nnode_max){
                nnode_max = nnode;
            }

            //parsing
            switch (e->whoAmI())
            {
            case 'R':
                m_resistors.push_back(e);
                break;
            case 'C':
                m_capacitors.push_back(e);
                break;
            case 'L':
                m_inductors.push_back(e);
                break;
            case 'V':
                this->m_total_vsources++; //total number of independant voltage sources
                m_vsources.push_back(e);
                break;
            case 'J':
                this->m_total_jsources++;
                m_jsources.push_back(e);
                break;
            default:
                throw std::invalid_argument("Invalid component name: "
                     + std::string(1, e->whoAmI())
                     + std::to_string(e->getId()));
            }
        }

        this->m_total_nodes = std::max(pnode_max, nnode_max); // total number of nodes
}

double Circuit::validateFrequency(double frequency){
    if(frequency < F_LIM){
        throw std::invalid_argument("Frequency cannot be negative or zero! Invalid frequency: "
                + std::to_string(frequency));
    }
    return frequency;
}