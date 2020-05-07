#include "Cities.h"
#include <algorithm>
#include <iomanip>

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
    float min_cost;
    std::vector<city_node> min_path;
    permutePath(os, current_path_bools, current_path, current_path_bools[0].first, min_cost, min_path);
    os << "\nMinumum Cost: " << std::fixed << std::setprecision(2) << min_cost << " with path";
    std::cout << "\nMinumum Cost: " << std::fixed << std::setprecision(2) << min_cost << " with path";
    for(auto it: min_path)
    {
        os << "->" << it.getName();
        std::cout << "->" << it.getName();
    }
    os << std::endl;
    std::cout << std::endl;

}

float Cities::getTravelCost(city_node &city_a, city_node &city_b)
{
    int neighbor_index = 0;
    for(int i=0; i<city_a.getNeighborCount(); i++)
    {
        if(city_a.getNeighbor(i)->getName() == city_b.getName())
            break;
        neighbor_index++;
    }
    return city_a.getNeighborCost(neighbor_index);
}

void Cities::permuteBack(std::ostream &os, std::vector<std::pair<city_node, bool>> bools, std::vector<city_node> path, city_node destination, float &minCost, std::vector<city_node> &minPath)
{
    //Basically same functiono as permutePath with different base case
    //Compare string names to see if we've traversed back to Reno
    if(path.back().getName() == destination.getName())
    {
        //Finally print what we have
        for(auto it: path)
            os << "->" << it.getName();
        os << std::endl;

        //Calculate min. if less than minCost, update
        float current_cost = 0;
        for(auto it = path.begin(); it != path.end()-1; it++)
            current_cost += getTravelCost(*it, *(it+1));
        os << "Path Cost: " << std::fixed << std::setprecision(2) << current_cost << std::endl;
        if(minCost < 1)
        {
            minCost = current_cost;
            minPath = path;
        }
        if(current_cost < minCost)
        {
            minCost = current_cost;
            minPath = path;
        }
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
            permuteBack(os, bools, path, destination, minCost, minPath);
            //After loop, reset so new path can be made
            bools[relative_index].second = false;
            path.pop_back();
        }
    }
}

void Cities::permutePath(std::ostream &os, std::vector<std::pair<city_node, bool>> bools, std::vector<city_node> path, city_node destination, float &minCost, std::vector<city_node> &minPath)
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
        //Reset bools for reverse traversal
        for(auto &it: bools)
            it.second = false;
        //Current path will be passed to continue onward of each forward permutation
        
        //end of the line so base case for forward traversal
        return permuteBack(os, bools, path, destination, minCost, minPath);
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
            permutePath(os, bools, path, destination, minCost, minPath);
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

