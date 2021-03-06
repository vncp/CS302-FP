

#ifndef _CITIES_
#define _CITIES_

#include <vector>
#include <iostream>
#include "city_node.h"

class Cities{
private:
    std::vector<city_node> m_cities;
protected: 
    //Returns the city node associated wiith a string, if not found then
    //it will return a null_ptr
    std::vector<city_node>::iterator searchName(const std::string name, bool &success);
    //Returns min
    void permuteBack(std::ostream &os, std::vector<std::pair<city_node, bool>> bools, std::vector<city_node> path, city_node destination, float &minCost, std::vector<city_node> &minPath);
    void permutePath(std::ostream &os, std::vector<std::pair<city_node, bool>> bools, std::vector<city_node> path, city_node destination, float &minCost, std::vector<city_node> &minPath);
    void rotateVector(std::vector<city_node>::iterator beg, std::vector<city_node>::iterator mid, std::vector<city_node>::iterator end);
    float getTravelCost(city_node &city_a, city_node &city_b);
public:
    //void permute(city_node current, const std::string start_name);

    //CTOR that takes a filename and initializes a bunch of cities

    //Basic Public Functions
    bool addCity(const std::string cityName);
    bool removeCity(std::string cityName);
    bool addNeighbor(const std::string cityName, const std::string neighborName, const float distance);
    
    //Must remove neighbors from both ends
    bool removeNeighbor(std::string cityName, std::string neighborName);
    
    void printData();
    //File I/O
    //-Input City Data from CSV
    //-Output Paths Data to CSV

    //Returns a list of all the possible paths and their distances
    //from a city and back given a starting city node
    void printPaths(std::ostream &os);
};

#include "Cities.cpp"

#endif