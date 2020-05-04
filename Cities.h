#ifndef _CITIES_
#define _CITIES_

#include "city_node.h"

class Cities{
private:
    std::vector<city_node> m_cities;
protected: 
    //Returns the city node associated wiith a string, if not found then
    //it will return a null_ptr
    city_node *searchName(std::string name);
public:
    //CTOR that takes a filename and initializes a bunch of cities
    Cities();

    //Basic Public Functions
    void addCity(std::string cityName);
    bool removeCity(std::string cityName);
    bool addNeighbor(std::string cityName, std::string neighborName, const float distance);
    
    //Must remove neighbors from both ends
    bool removeNeighbor(std::string cityName, std::string neighborName);
    
    //File I/O
    //-Input City Data from CSV
    //-Output Paths Data to CSV

    //Returns a list of all the possible paths and their distances
    //from a city and back given a starting city node
    void printPaths(const city_node &city);
};

#include "Cities.cpp"

#endif