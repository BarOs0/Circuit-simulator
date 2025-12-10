#pragma once

#include <complex>
#include <array>
#include <vector>
#include <stdexcept>

namespace bo{

    /**
     * @brief Base class for all elements in circuit theory
     * 
     * Element represents an electronic component:
     * - Resistor
     * - Capacitor
     * - Inductor
     * - Independent voltage source
     * - Independent current source
     * 
     * Contains information about type, nodes and ID
     */
    class Element {

        public:

            /**
             * @brief Returns type of the element
             * @return Character which identifies type of the element ('R', 'C', 'L', 'V', 'J')
             */
            char whoAmI() const;

            /**
             * @brief Returns unique index of element
             * @return Element ID
             */
            unsigned int getId() const;

            /**
             * @brief Returns nodes of the element
             * @return Array filled with node numbers {pnode, node}
             */
            std::array<unsigned int, 2> getEndpoints() const;

            /**
             * @brief Sets new nodes of the element
             * @param pnode Positive node number
             * @param nnode Negative node number
             * @throw std::invalid_argument if pnode == nnode
             */
            void setEndpoints(unsigned int pnode, unsigned int nnode);

            /**
             * @brief Checks if elements have the same fixed node
             * @param other Other element to compare
             * @param node Common node
             * @return true if this and other are connected through "node", otherwise false
             * @throw std::invalid_argument if node == 0 (GND)
             */
            bool isNeighbour(const Element& other, unsigned int node) const;

            /**
             * @brief Checks if elements have the same node
             * @param other Other element to compare
             * @return true if this and other are connected through the same node, otherwise false
             */
            bool isNeighbour(const Element& other) const;

            /// Virtual destructor for the Element class
            virtual ~Element() = default;

        protected:

            /**
             * @brief Protected constructor for derived classes
             * @param val Element value (real)
             * @param pnode Positive node number
             * @param nnode Negative node number
             * @param type Element type
             * @throw std::invalid_argument if pnode == nnode
             */
            Element(unsigned int pnode, unsigned int nnode, char type);

        private:

            /// Element counters for unique ID
            inline static unsigned int r_counter = 1; ///< Resistor counter
            inline static unsigned int c_counter = 1; ///< Capacitor counter
            inline static unsigned int l_counter = 1; ///< Inductor counter
            inline static unsigned int v_counter = 1; ///< Independent voltage sources counter
            inline static unsigned int j_counter = 1; ///< Independent current sources counter

            std::array<unsigned int, 2> m_endpoints; ///< Array for the nodes [pnode, nnode]

            unsigned int m_id; ///< Unique element ID

            char m_type; ///< Element type ('R', 'C', 'L', 'V', 'J')

            /**
             * @brief Validates nodes
             * @param endpoints Nodes array
             * @return Validated nodes array
             * @throw std::invalid_argument if pnode == nnode
             */
            static std::array<unsigned int, 2> validateEndpoints(const std::array<unsigned int, 2> &endpoints);
    };
    
}