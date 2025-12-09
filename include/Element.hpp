#pragma once

#include <complex>
#include <array>
#include <vector>
#include <stdexcept>

namespace bo{

    constexpr double E_LIM = 1e-14;

    class Element {
        public:

            char whoAmI() const;

            unsigned int getId() const;

            std::array<unsigned int, 2> getEndpoints() const;

            void setEndpoints(unsigned int pnode, unsigned int nnode);

            double getValue() const;

            void setValue(double val);

            bool isNeighbour(const Element& other, unsigned int node) const;

            bool isNeighbour(const Element& other) const;

            virtual ~Element() = default;

        private: // here because type should be initialized before m_value (validateVal in Element.cpp)

            char m_type;

        protected:

            double m_value;

            Element(double val, unsigned int pnode, unsigned int nnode, char type);

        private:

            inline static unsigned int r_counter = 1;

            inline static unsigned int c_counter = 1;

            inline static unsigned int l_counter = 1;

            inline static unsigned int v_counter = 1;
            
            inline static unsigned int j_counter = 1;

            std::array<unsigned int, 2> m_endpoints;

            unsigned int m_id;

            static double validateVal(double val, char type);

            static std::array<unsigned int, 2> validateEndpoints(const std::array<unsigned int, 2> &endpoints);
    };
    
}