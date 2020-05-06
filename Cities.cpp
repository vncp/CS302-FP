#include "Cities.h"

std::vector<city_node>::iterator Cities::searchName(const std::string name, bool &success)
{
    for(std::vector<city_node>::iterator it=m_cities.begin(); it!=m_cities.end(); it++)
    {
        if(it->getName() == name)
        {
            success = true;
            return it;
        }
    }
    success = false;
    return m_cities.end();
}

bool Cities::addCity(const std::string cityName)
{
    //City w/ name already exists
    bool successful = false;
    searchName(cityName, successful);
    if(successful)
    {
        std::cout << "Error: " << cityName << " already exists!\n";
        return false;
    }
    else
    {
        std::cout << "Adding " << cityName << ".\n";
        city_node *temp_ptr = new city_node(cityName);
        m_cities.push_back(*temp_ptr);
        delete temp_ptr;
        temp_ptr = nullptr;
    }
    return true;
}

bool Cities::removeCity(const std::string cityName)
{
    bool successful = false;
    auto it = searchName(cityName, successful);
    if(!successful)
        return false;
    else
    {
        m_cities.erase(it);
    }
    return true;
}

bool Cities::addNeighbor(const std::string cityName, const std::string neighborName, const float distance)
{
    bool successful_1 = false, successful_2 = false;
    auto it_1 = searchName(cityName, successful_1), it_2 = searchName(neighborName, successful_2);
    if(!successful_1 || !successful_2)
    {
        if(!successful_1)
            std::cout << cityName << " could not be found!\n";
        if(!successful_2)
            std::cout << neighborName << " could not be found!\n";
        return false;
    }
    else
        it_1->addNeighbor(*it_2, distance);
    return true;
}

void Cities::printData()
{
    std::cout << "Printing City Data\n";
    for(auto it:m_cities)
    {
        for(int i=0; i<it.getNeighborCount(); i++)
        {
            std::cout << it.getName() << "'s Neighbor is ";
            std::cout << it.getNeighbor(i)->getName() << std::endl;
        }

    }
}

void Cities::printPaths(std::ostream &os)
{
    std::vector<std::pair<city_node, int>> traversed;
    for(auto it:m_cities)
        traversed.push_back(std::make_pair(it, 0));

    
    permutePath(traversed, &traversed[0].first);
    
}

void Cities::permutePath(std::vector<std::pair<city_node, int>> city, city_node *current)
{
    //Print Name
    std::cout << current->getName() << std::endl;
    //Iterate count of city
    int current_index=0;
    for(auto it:city)
    {
        if(current->getName() == it.first.getName())
            break;
        current_index++;
    }
    //Iterate current by one
    city[current_index].second++;
    //Loop through Neighbors
    for(int i=0;i<current->getNeighborCount();i++)
    {
        //Find Neighbors Index Relative to city
        int neighbor_index=0;
        for(auto it: city)
        {
            if(it.first.getName() == current->getNeighbor(i)->getName())
                break;
            neighbor_index++;
        }
        //std::cout << "Checking neighbor of " << current->getName() << ": " << city[neighbor_index].first.getName() << std::endl;
        //std::cout << city[neighbor_index].second << " vs " << city[current_index].second << std::endl;
        //If This Neighbor's Index < Current Index, do Recursive Call
        if(city[neighbor_index].second < city[current_index].second)
            permutePath(city, current->getNeighbor(i));
    }
}