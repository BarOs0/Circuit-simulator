#pragma once

#include <iostream>

#include <vector>
#include <array>

#include <complex>

class Element{

public:

    static unsigned int r_counter;
    static unsigned int c_counter;
    static unsigned int l_counter;
    static unsigned int v_counter;

    char whoAmI(void) const {return this->m_type;}

    unsigned int getId(void) const {return this->m_id;}

    virtual std::complex<double> getAdmitance(double freqency) const = 0;

    void getEndpoints(int &pnode, int &nnode) const {
        pnode = this->m_endpoints[0];
        nnode = this->m_endpoints[1];
    }

    bool isNeighbour(const Element& other, int node) const {
        if(node != 0){
           return   (this->m_endpoints[0] == node || this->m_endpoints[1] == node) && 
                    (other.m_endpoints[0] == node || other.m_endpoints[1] == node);
        }
        else{
            std::cout << "Common node cannot be GND!" << std::endl;
            return false;
        }
    }
    
    bool isNeighbour(const Element& other) const { // method overload
        return  (this->m_endpoints[0] == other.m_endpoints[0] && this->m_endpoints[0] != 0) ||
                (this->m_endpoints[1] == other.m_endpoints[1] && this->m_endpoints[1] != 0) ||
                (this->m_endpoints[0] == other.m_endpoints[1] && this->m_endpoints[0] != 0) ||
                (this->m_endpoints[1] == other.m_endpoints[0] && this->m_endpoints[1] != 0);
    }

private:

    unsigned int m_id;

protected:

    char m_type;
    double m_value;
    std::array<int, 2> m_endpoints;

    Element(double val, int pnode, int nnode, unsigned int id, char type) : m_id(id), m_type(type){
        if(val <= 0){
            std::string exc = "Value must be positive double!";
            throw exc;
        }

        if(pnode < 0 || nnode < 0){
            std::string exc = "Both + and - nodes must be positive integers or 0";
            throw exc;
        }
        this->m_value = val;
        this->m_endpoints = {pnode, nnode};
    }

    double getValue(void) const {return this->m_value;}

    void setValue(double val){
        if(val <= 0){
            std::string exc = "Value must be positive double!";
            throw exc;
        }
        this->m_value = val;
    }

    virtual ~Element() = default;
};

unsigned int Element::r_counter{1};
unsigned int Element::c_counter{1};
unsigned int Element::l_counter{1};
unsigned int Element::v_counter{1};

class Resistance : public Element{

public:

    Resistance(double r, int pnode, int nnode) : Element(r, pnode, nnode, this->r_counter++, 'R'){}

    std::complex<double> getAdmitance(double freqency) const override {
        return std::complex<double>((1 / (this->m_value)), 0.0);
    }
};

class Capacitance : public Element{

public:

    Capacitance(double c, int pnode, int nnode) : Element(c, pnode, nnode, this->c_counter++, 'C'){}

    std::complex<double> getAdmitance(double freqency) const override {
        return std::complex<double>(0.0, (2 * M_PI * freqency) * (this->m_value));
    }
};

class Inductance : public Element{

public: 

    Inductance(double l, int pnode, int nnode) : Element(l, pnode, nnode, this->l_counter++, 'L'){}

    std::complex<double> getAdmitance(double freqency) const override {
        return std::complex<double>(0.0, (-1) / ((2 * M_PI * freqency) * (this->m_value)));
    }
};

class IndependantV : public Element{

public: 

    IndependantV(double v, int pnode, int nnode) : Element(v, pnode, nnode, this->v_counter++, 'V'){}

    std::complex<double> getAdmitance(double freqency) const override {
        return std::complex<double>(0.0, 0.0);
    }
};

class Circuit{

private:

    std::vector<Element*> m_resistors, m_capacitors, m_inductors, m_vsources, m_components;
    std::vector<std::vector<std::complex<double>>> m_A, m_G, m_B, m_C, m_D;
    unsigned int m_total_nodes{0}; // n
    unsigned int m_total_vsources{0}; // m
    double m_frequency;

    void buildCircuit(const std::vector<Element*> &elements){

        int pnode_max = 0;
        int nnode_max = 0;
        int pnode = 0;
        int nnode = 0;

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
            default:
                std::cout << "Invalid component name: " << e->whoAmI() << e->getId() << std::endl;
                break;
            }
        }

        this->m_total_nodes = std::max(pnode_max, nnode_max); // total number of nodes
    }
    
public:

    Circuit(const std::vector<Element*> &elements, double freq) : m_components(elements), m_frequency(freq){

        if(freq < 1e-12){
            std::string exc = "Frequency cannot be zero or negative!"; // dzielenie przez ZERO w funkcjach admitancji (L)!!!
            throw exc;
        }

        this->m_frequency = freq;

        buildCircuit(elements);
    }


//     // TO MI COS ZLE LICZY NIEEEE BEDE LICZYYYYYL
//     std::complex<double> same_node_sum(int node){
//         std::complex<double> sum = 0;
//         for(int i = 0; i < m_components.size(); i++){
//             for(int j = 0; j < m_components.size(); j++){
//                 if(m_components[i]->isNeighbour(*m_components[j], node)){
//                     sum = m_components[i]->getAdmitance(m_frequency) + m_components[j]->getAdmitance(m_frequency);
//                 }
//                 else {
//                     continue;
//                 }
//             }
//         }
//         return sum;
//     }
};