#include "Element.hpp"

namespace bo{

    Element::Element(unsigned int pnode, unsigned int nnode, char type) 
                    : m_endpoints{validateEndpoints({pnode, nnode})}, m_type(type){

        switch(type){
            case 'R':
                m_id = r_counter++;
                break;
            case 'C':
                m_id = c_counter++;
                break;
            case 'L':
                m_id = l_counter++;
                break;
            case 'V':
                m_id = v_counter++;
                break;
            case 'J':
                m_id = j_counter++;
                break;
            default:
                throw std::invalid_argument("Invalid element type! Invalid type: "
                            + std::string(1, type));
        }
    }

    char Element::whoAmI() const {return m_type;}

    unsigned int Element::getId() const {return m_id;}

    std::array<unsigned int, 2> Element::getEndpoints() const {return m_endpoints;}

    void Element::setEndpoints(unsigned int pnode, unsigned int nnode){
        m_endpoints = validateEndpoints({pnode, nnode});
    }

    bool Element::isNeighbour(const Element& other, unsigned int node) const {
        if(node != 0){
            return (this->m_endpoints[0] == node || this->m_endpoints[1] == node) && 
                (other.m_endpoints[0] == node || other.m_endpoints[1] == node);
        }
        else{
            throw std::invalid_argument("Common node cannot be GND!");
        }
    }

    bool Element::isNeighbour(const Element& other) const {
        return (this->m_endpoints[0] == other.m_endpoints[0] && this->m_endpoints[0] != 0) ||
            (this->m_endpoints[1] == other.m_endpoints[1] && this->m_endpoints[1] != 0) ||
            (this->m_endpoints[0] == other.m_endpoints[1] && this->m_endpoints[0] != 0) ||
            (this->m_endpoints[1] == other.m_endpoints[0] && this->m_endpoints[1] != 0);
    }

    std::array<unsigned int, 2> Element::validateEndpoints(const std::array<unsigned int, 2> &endpoints){
        if(endpoints[0] == endpoints[1]){
            throw std::invalid_argument("Pnode and nnode cannot be the same!");
        }
        return endpoints;
    }
    
}