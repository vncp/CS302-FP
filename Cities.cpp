#include "Cities.h"
#include <iostream>

void Cities::printPaths(const city_node &city)
{
    //Create copy of the current city graph;
    std::vector<city_node> graph_copy(m_cities);
    //If current graph is empty don't return anything
    if(graph_copy.empty())
        return;
    if(!city.getNeighborCount())
    {
        std::cout << "Path 1: " << city.getName();
        return; 
    }
    while(city.getNeighborCount())
    {
        
    }
    
    


}