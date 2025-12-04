#include "Element.hpp"

Element::Element(double val, unsigned int pnode, unsigned int nnode, char type) 
                : m_type(type), 
                m_value(validateVal(val)),
                m_endpoints{validateEndpoints({pnode, nnode})}{

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

double Element::getValue() const {return m_value;}

void Element::setValue(double val){m_value = validateVal(val);}

bool Element::isNeighbour(const Element& other, unsigned int node) const {
    if(node != 0){
        return (this->m_endpoints[0] == node || this->m_endpoints[1] == node) && 
               (other.m_endpoints[0] == node || other.m_endpoints[1] == node);
    }
    else{
        throw std::invalid_argument("Common node cannot be GND for this function, please abort node parameter!");
    }
}

bool Element::isNeighbour(const Element& other) const { // method overload
    return (this->m_endpoints[0] == other.m_endpoints[0] && this->m_endpoints[0] != 0) ||
           (this->m_endpoints[1] == other.m_endpoints[1] && this->m_endpoints[1] != 0) ||
           (this->m_endpoints[0] == other.m_endpoints[1] && this->m_endpoints[0] != 0) ||
           (this->m_endpoints[1] == other.m_endpoints[0] && this->m_endpoints[1] != 0);
}

double Element::validateVal(double val){
    if(val < E_LIM){
        throw std::invalid_argument("Value must be positive double! Invalid value: "
                    + std::to_string(val));
    }
    return val;
}

std::array<unsigned int, 2> Element::validateEndpoints(const std::array<unsigned int, 2> &endpoints){
    if(endpoints[0] == endpoints[1]){
        throw std::invalid_argument("Pnode and nnode cannot be the same!");
    }
    return endpoints;
}
// Element::~Element(){std::cout << "Element destructor!" << std::endl;} //debug