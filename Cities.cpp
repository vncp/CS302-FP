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
        return false;
    else
    {
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
        return false;
    else
        it_1->addNeighbor(*it_2, distance);
    return true;
}

void Cities::printData()
{
    std::cout << "Printing City Data\n";
    for(auto it:m_cities)
    {
        std::cout << it.getName() << "'s Neighbor is " << it.getNeighbor()->getName() << std::endl;
    }
}