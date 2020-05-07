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

class neighbor;

class city_node{
protected:
    std::vector<neighbor> m_neighbors;
    std::string m_name;
public:
    //Parameterized CTOR, requires a name to create a city_node
    city_node(std::string name);
    //Copy CTOR
    city_node(const city_node &city_copy);
    //Connects two city_nodes together via member sof hte neighbor class
    city_node &operator=(const city_node &rhs);
    bool operator==(const city_node &rhs);
    void addNeighbor(city_node &city, const float distance);
    //Returns the name of the current city_node
    std::string getName() const;
    //Gets the number of neighbors connected to the current city
    int getNeighborCount() const;
    //Returns neighbor of the current city_node via index
    city_node* getNeighbor(int index=0);
    float getNeighborCost(int index=0);
};

float city_node::getNeighborCost(int index)
{
    return m_neighbors[index].getCost();
}

bool city_node::operator==(const city_node &rhs)
{
    if(rhs.getName() == m_name)
        return true;
    else
        return false;
}   

city_node &city_node::operator=(const city_node &rhs)
{
    if(this != &rhs)
    {
        m_name = rhs.m_name;
        m_neighbors = rhs.m_neighbors;
    }
    return *this;
}

city_node::city_node(const std::string name) : m_name(name)
{
}

city_node::city_node(const city_node &city_copy) : m_name(city_copy.m_name), m_neighbors(city_copy.m_neighbors)
{
}
void city_node::addNeighbor(city_node &city, const float distance)
{
    neighbor *temp_ptr = new neighbor(&city, distance);
    m_neighbors.push_back(*temp_ptr);
    temp_ptr = new neighbor(this, distance);
    city.m_neighbors.push_back(*temp_ptr);
    delete temp_ptr;
}

std::string city_node::getName() const{
    return m_name;
}

int city_node::getNeighborCount() const{
    return m_neighbors.size();
}

city_node *city_node::getNeighbor(int index)
{
    if(index < 0 || index > m_neighbors.size()-1)
    {
        return NULL;
    }
    return m_neighbors[index].getNeighbor();
}

#endif