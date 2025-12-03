#pragma once

#include <iostream>

#include <vector>
#include <array>

#include <complex>

#define E_LIM 1e-14
#define F_LIM 1e-12

class Element{

private:

    unsigned int m_id;

protected:

    char m_type;
    double m_value;
    std::array<int, 2> m_endpoints;

    Element(double val, int pnode, int nnode, unsigned int id, char type) : m_id(id), m_type(type){
        if(val < E_LIM){
            std::string exc = "Value must be positive double!";
            throw exc;
        }

        if(pnode < 0 || nnode < 0){
            std::string exc = "Both + and - nodes must be positive integers or 0 for GND";
            throw exc;
        }
        this->m_value = val;
        this->m_endpoints = {pnode, nnode};
    }

    double getValue(void) const {return this->m_value;}

    void setValue(double val){
        if(val < E_LIM){
            std::string exc = "Value must be positive double!";
            throw exc;
        }
        this->m_value = val;
    }

    public:

    static unsigned int r_counter;
    static unsigned int c_counter;
    static unsigned int l_counter;
    static unsigned int v_counter;

    char whoAmI(void) const {return this->m_type;}

    unsigned int getId(void) const {return this->m_id;}

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
            std::cout << "Common node cannot be GND for this function, please abort node parameter!" << std::endl;
            return false;
        }
    }
    
    bool isNeighbour(const Element& other) const { // method overload
        return  (this->m_endpoints[0] == other.m_endpoints[0] && this->m_endpoints[0] != 0) ||
                (this->m_endpoints[1] == other.m_endpoints[1] && this->m_endpoints[1] != 0) ||
                (this->m_endpoints[0] == other.m_endpoints[1] && this->m_endpoints[0] != 0) ||
                (this->m_endpoints[1] == other.m_endpoints[0] && this->m_endpoints[1] != 0);
    }

};

unsigned int Element::r_counter{1};
unsigned int Element::c_counter{1};
unsigned int Element::l_counter{1};
unsigned int Element::v_counter{1};

class Passive : public Element{ //PASSIVE ELEMENTS

protected:

    Passive(double val, int pnode, int nnode, char type) : Element(val, pnode, nnode, this->v_counter++, type){}

    virtual std::complex<double> getAdmitance(double frequency) const = 0;

public:

    virtual ~Passive() = default;

};

class Active : public Element{ //ACTIVE ELEMENTS

protected:

    Active(double val, int pnode, int nnode, char type) : Element(val, pnode, nnode, this->v_counter++, type){}
};

class Resistance : public Passive{

public:

    Resistance(double r, int pnode, int nnode) : Passive(r, pnode, nnode, 'R'){}

    std::complex<double> getAdmitance(double frequency) const override {
        return std::complex<double>((1 / (this->m_value)), 0.0);
    }
};

class Capacitance : public Passive{

public:

    Capacitance(double c, int pnode, int nnode) : Passive(c, pnode, nnode, 'C'){}

    std::complex<double> getAdmitance(double frequency) const override {
        return std::complex<double>(0.0, (2 * M_PI * frequency) * (this->m_value));
    }
};

class Inductance : public Passive{

public: 

    Inductance(double l, int pnode, int nnode) : Passive(l, pnode, nnode, 'L'){}

    std::complex<double> getAdmitance(double frequency) const override {
        return std::complex<double>(0.0, (-1) / ((2 * M_PI * frequency) * (this->m_value)));
    }
};

class IndependantV : public Active{

public: 

    IndependantV(double v, int pnode, int nnode) : Active(v, pnode, nnode, 'V'){}
};

class IndependantJ : public Active{

public: 

    IndependantJ(double j, int pnode, int nnode) : Active(j, pnode, nnode, 'J'){}
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

    Circuit(const std::vector<Element*> &elements, double frequency) : m_components(elements), m_frequency(frequency){

        if(frequency < F_LIM){
            std::string exc = "Frequency cannot be zero or negative!"; // dzielenie przez ZERO w funkcjach admitancji (L)!!!
            throw exc;
        }

        this->m_frequency = frequency;

        buildCircuit(elements);
    }

    double getFrequency(void) const {return this->m_frequency;}

    void setFrequency(double frequency){
        if(frequency < F_LIM){
            std::string exc = "Frequency cannot be zero or negative!"; // dzielenie przez ZERO w funkcjach admitancji (L)!!!
            throw exc;
        }
        this->m_frequency = frequency;
    }
};