#include "Circuit.hpp"

Circuit::Circuit(const std::vector<Element*> &elements, double frequency)
                : m_components(elements), m_frequency(validateFrequency(frequency)){

    buildCircuit(elements);
    m_total_vsources = m_vsources.size();
    m_total_jsources = m_jsources.size();
}

double Circuit::getFrequnecy() const {return m_frequency;}

void Circuit::setFrequency(double frequency){m_frequency = validateFrequency(frequency);}

unsigned int Circuit::getTotalNodes() const {return m_total_nodes;}

unsigned int Circuit::getTotalVsources() const {return m_total_vsources;}

unsigned int Circuit::getTotalJsources() const {return m_total_jsources;}

void Circuit::buildCircuit(const std::vector<Element*> &elements){
    
       std::array<unsigned int, 2> nodes_max = {0, 0};

        for(auto e : elements){

            //looking for total number of nodes
            std::array<unsigned int, 2> nodes = e->getEndpoints();
            if(nodes[0] > nodes_max[0]){
                nodes_max[0] = nodes[0];
            }
            else if(nodes[1] > nodes_max[1]){
                nodes_max[1] = nodes[1];
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
                m_vsources.push_back(e);
                break;
            case 'J':
                m_jsources.push_back(e);
                break;
            default:
                throw std::invalid_argument("Invalid component name: "
                     + std::string(1, e->whoAmI())
                     + std::to_string(e->getId()));
            }
        }

        this->m_total_nodes = std::max(nodes_max[0], nodes_max[1]); // total number of nodes
}

double Circuit::validateFrequency(double frequency){
    if(frequency < F_LIM){
        throw std::invalid_argument("Frequency cannot be negative or zero! Invalid frequency: "
                + std::to_string(frequency));
    }
    return frequency;
}