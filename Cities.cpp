#include "Cities.h"
#include <algorithm>

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
    //Attempt - Passed Vector
    /*
    std::vector<city_node> passed;
    for(unsigned i = 0; i<m_cities[0].getNeighborCount(); i++)
    {
        std::cout << "New Path: \n";
        std::cout << m_cities[0].getName() << std::endl;
        passed.push_back(m_cities[0]);
        int distance = 0;
        permutePath(*m_cities[0].getNeighbor(i), passed);
    }
    */
    //Attempt - Rotate City Copy Array;
    std::vector<city_node> cities_cpy;
    cities_cpy.reserve(m_cities.size());
    for(int i=0; i<m_cities.size()-1; i++)
    {
        cities_cpy.push_back(m_cities[i]);
        std::cout << m_cities[i].getName() << std::endl;
    }
    //Rotate


    for(int i=0; i<cities_cpy.size()-2; i++)
    {
        for(int j=0; j<cities_cpy.size()-3; j++)
        {
            for(int k=0; k<cities_cpy.size()-4; k++)
            {
                for(int l=0; l<cities_cpy.size()-5; l++)
                {
                    std::cout << "Path: ";
                    for(auto it=cities_cpy.begin(); it!=cities_cpy.end()-1; it++)
                        std::cout << it->getName() << " -> ";
                    std::cout << std::endl;                   
                    std::rotate(cities_cpy.begin()+4, cities_cpy.begin()+5, cities_cpy.end()-1);
                }
                std::rotate(cities_cpy.begin()+3, cities_cpy.begin()+4, cities_cpy.end()-1);
            }
            std::rotate(cities_cpy.begin()+2, cities_cpy.begin()+3, cities_cpy.end()-1);
        }
        std::rotate(cities_cpy.begin()+1, cities_cpy.begin()+2, cities_cpy.end()-1);
    }                
}

void Cities::rotateVector(std::vector<city_node>::iterator beg, std::vector<city_node>::iterator mid, std::vector<city_node>::iterator end)
{
    if(mid!=beg)
    {
        //Save front
        city_node temp = *beg;
        //replace i-1 with i until i=end
        auto curr_next = beg;
        for(auto curr=beg+1; curr != end; curr++)
            *curr_next++ = *curr;
        *(end-1) = temp;
        rotateVector(beg, mid-1, end);
    }
}

void Cities::permutePath(city_node next, std::vector<city_node> passed)
{
    //Attempt - Passed Vector
    /*
    passed.push_back(next);
    for(unsigned i = 0; i<next.getNeighborCount(); i++)
    {
        std::cout << next.getName() << std::endl;
        bool new_path = true;
        for(auto it : passed)
            if(it == *next.getNeighbor(i))
                new_path = false;
        if(new_path)
            permutePath(*next.getNeighbor(i), passed);
    }
    */
}