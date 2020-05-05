#include "Cities.h"

city_node *Cities::searchName(const std::string name)
{
    city_node *city_ptr;
    for(auto i: m_cities)
    {
        if(i.getName() == name)
        {
            city_ptr = &i;
            return city_ptr;
        }
    }
    return nullptr;
}

bool Cities::addCity(const std::string cityName)
{
    //City w/ name already exists
    if(searchName(cityName))
    {
        return false;
    }
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

    city_node *del_ptr = searchName(cityName);
    if(!del_ptr)
    {
        return false;
    }
    for(auto it = m_cities.begin(); it!=m_cities.end(); it++)
    {
        std::string name = it->getName();
        if(name == del_ptr->getName())
        {
            m_cities.erase(it);
            return true;
        }
    }                                                                
    return false;
}

bool Cities::addNeighbor(const std::string cityName, const std::string neighborName, const float distance)
{
    if(!searchName(cityName) || !searchName(neighborName))
    {
        return false;
    }
    searchName(cityName)->addNeighbor(*searchName(neighborName), distance);
    return true;
}

void Cities::printData(std::string cityName)
{
    city_node *temp_ptr = searchName(cityName);
    std::cout << temp_ptr->getName() << "'s neighbor: " << temp_ptr->getNeighbor() << std::endl;
}