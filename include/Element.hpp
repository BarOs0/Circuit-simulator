#pragma once

#include <complex>
#include <array>
#include <vector>
#include <stdexcept>

#define E_LIM 1e-14

class Element {
    public:

        inline static unsigned int r_counter = 1;

        inline static unsigned int c_counter = 1;

        inline static unsigned int l_counter = 1;

        inline static unsigned int v_counter = 1;
        
        inline static unsigned int j_counter = 1;

        char whoAmI() const;

        unsigned int getId() const;

        std::array<unsigned int, 2> getEndpoints() const;

        void setEndpoints(unsigned int pnode, unsigned int nnode);

        double getValue() const;

        void setValue(double val);

        bool isNeighbour(const Element& other, unsigned int node) const;

        bool isNeighbour(const Element& other) const;

        virtual ~Element() = default;

    protected:

        char m_type;

        double m_value;

        std::array<unsigned int, 2> m_endpoints;

        Element(double val, unsigned int pnode, unsigned int nnode, char type);

    private:

        unsigned int m_id;

        static double validateVal(double val);

        static std::array<unsigned int, 2> validateEndpoints(const std::array<unsigned int, 2> &endpoints);
};