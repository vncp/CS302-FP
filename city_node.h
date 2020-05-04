/*
City_node class used as the vertices for the graph data structure which represents interconnected
cities. The edges are represented by neighbors with weighted edges corresponding to their distances
from each other. Multiple edges/neighbors are handled by the vector from C++ STL.
*/

#ifndef _CITY_NODE_
#define _CITY_NDOE_

#include <vector>
#include "neighbor.h"
#include <string>

class city_node{
private:
    std::vector<neighbor> m_neighbors;
    const std::string m_name;
public:
    //Parameterized CTOR, requires a name to create a city_node
    city_node(const std::string name);
    //Connects two city_nodes together via member sof hte neighbor class
    void addNeighbor(const city_node *city, const float distance);
    //Returns the name of the current city_node
    std::string getName() const;
    //Gets the number of neighbors connected to the current city
    int getNeighborCount() const;
    //Returns neighbor of the current city_node via index
    city_node* getNeighbor(int index=0);
};

//#include city_node.cpp
#endif