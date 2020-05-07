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
    //Attempt - Passed Vector -> Can't print sequentially
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

    //Attempt - Rotate City Copy Array -> Rotate doesn't work on std::vector<city_node>
    /*
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
    */

    //Attempt - Recursive (Print after all Traversed)

    //Set bool to true once traversed
    std::vector<std::pair<city_node, bool>> current_path_bools;
    std::vector<city_node> current_path;
    //Start w/ clean path, all bools to false
    for(auto it: m_cities)
        current_path_bools.push_back(std::make_pair(it, false));
    current_path_bools.pop_back(); //Removes Atlantis
    
    //Recursive call to function for every neighbor, copies current_path for every iteration
    //If all bools are true, print current_path
    //Start with Reno
    current_path_bools[0].second = true;
    current_path.push_back(current_path_bools[0].first);

    permutePath(current_path_bools, current_path);
}

void Cities::permutePath(std::vector<std::pair<city_node, bool>> bools, std::vector<city_node> path)
{
    //Attempt Recursive(Print after all True)
    //If any bools are false, not finished
    bool finished = true;
    for(auto it: bools)
        if(it.second == false)
        {
            finished = false;
            break;
        }
    if(finished)
    {
        for(auto it: path)
            std::cout << "->" << it.getName();
        std::cout << "\n";
        //end of the line so base case
        return;
    }
    //Next item is path.back().getNeighbor()
    for(int i=0; i<path.back().getNeighborCount(); i++)
    {
        //Can only go to neighbor that has been unvisited, so must find its index in bools
        int relative_index = 0;
        for(auto it: bools)
        {
            if(path.back().getNeighbor(i)->getName() == it.first.getName())
                break;
            relative_index++;
        }
        //Take relative index, turn bool to true, add to current path.
        if(bools[relative_index].second == false)
        {
            bools[relative_index].second = true;
            path.push_back(bools[relative_index].first);
            permutePath(bools, path);
            //After loop, reset so new path can be made
            bools[relative_index].second = false;
            path.pop_back();
        }
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

