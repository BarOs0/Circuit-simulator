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
    std::array<unsigned int, 2> m_endpoints;

    Element(double val, unsigned int pnode, unsigned int nnode, char type) : m_type(type){ //id trzeba dodac
        if(val < E_LIM){
            std::string exc = "Value must be positive double!";
            throw exc;
        }
        this->m_value = val;
        this->m_endpoints = {pnode, nnode};

        switch(type){

            case 'R':
                this->m_id = this->r_counter++;
                break;
            case 'C':
                this->m_id = this->c_counter++;
                break;
            case 'L':
                this->m_id = this->l_counter++;
                break;
            case 'V':
                this->m_id = this->v_counter++;
                break;
            case 'J':
                this->m_id = this->j_counter++;
                break;
            default:
                std::cout << "Invalid element type!" << std::endl;
                break;
        }
    }

    public:

    inline static unsigned int r_counter = 1;
    inline static unsigned int c_counter = 1;
    inline static unsigned int l_counter = 1;
    inline static unsigned int v_counter = 1;
    inline static unsigned int j_counter = 1;

    char whoAmI(void) const {return this->m_type;}

    unsigned int getId(void) const {return this->m_id;}

    void getEndpoints(unsigned int &pnode, unsigned int &nnode) const {
        pnode = this->m_endpoints[0];
        nnode = this->m_endpoints[1];
    }

    void setEndpoints(unsigned int pnode, unsigned int nnode){
        this->m_endpoints[0] = pnode;
        this->m_endpoints[1] = nnode;
    }

    double getValue(void) const {return this->m_value;}

    void setValue(double val){
        if(val < E_LIM){
            std::string exc = "Value must be positive double!";
            throw exc;
        }
        this->m_value = val;
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

    virtual ~Element(){
        std::cout << "Element destructor!" << std::endl;
    }

};

class Passive : public Element{ //PASSIVE ELEMENTS

protected:

    Passive(double val, unsigned int pnode, unsigned int nnode, char type) : Element(val, pnode, nnode, type){}

    virtual std::complex<double> getAdmitance(double frequency) const = 0;

public:

    virtual ~Passive() = default;

};

class Active : public Element{ //ACTIVE ELEMENTS

protected:

    Active(double val, unsigned int pnode, unsigned int nnode, char type) : Element(val, pnode, nnode, type){}
};

class Resistance : public Passive{

public:

    Resistance(double r, unsigned int pnode, unsigned int nnode) : Passive(r, pnode, nnode, 'R'){}

    std::complex<double> getAdmitance(double frequency) const override {
        return std::complex<double>((1 / (this->m_value)), 0.0);
    }
};

class Capacitance : public Passive{

public:

    Capacitance(double c, unsigned int pnode, unsigned int nnode) : Passive(c, pnode, nnode, 'C'){}

    std::complex<double> getAdmitance(double frequency) const override {
        return std::complex<double>(0.0, (2 * M_PI * frequency) * (this->m_value));
    }
};

class Inductance : public Passive{

public: 

    Inductance(double l, unsigned int pnode, unsigned int nnode) : Passive(l, pnode, nnode, 'L'){}

    std::complex<double> getAdmitance(double frequency) const override {
        return std::complex<double>(0.0, (-1) / ((2 * M_PI * frequency) * (this->m_value)));
    }
};

class IndependantV : public Active{

public: 

    IndependantV(double v, unsigned int pnode, unsigned int nnode) : Active(v, pnode, nnode, 'V'){}
};

class IndependantJ : public Active{

public: 

    IndependantJ(double j, unsigned int pnode, unsigned int nnode) : Active(j, pnode, nnode, 'J'){}
};

class Circuit{

private:

    std::vector<Element*> m_resistors, m_capacitors, m_inductors, m_vsources, m_components, m_jsources;
    std::vector<std::vector<std::complex<double>>> m_A, m_G, m_B, m_C, m_D;
    unsigned int m_total_nodes{0}; // n
    unsigned int m_total_vsources{0}, m_total_jsources{0}; // m
    double m_frequency;

    void buildCircuit(const std::vector<Element*> &elements){

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