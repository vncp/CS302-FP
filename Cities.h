#ifndef _CITIES_
#define _CITIES_

#include "city_node.h"

class Cities{
private:
    std::vector<city_node> m_cities;
protected: 
    //Returns the city node associated wiith a string, if not found then
    //it will set the referenced bool to false and return a null_ptr
    city_node *searchName(std::string name, bool &successful);
public:
    //CTOR that takes a filename and initializes a bunch of cities
    Cities();

    //Basic Public Functions
    void addCity(std::string cityName);
    bool removeCity(std::string cityName);
    bool addNeighbor(std::string cityName, std::string neighborName, const float distance);
    bool removeNeighbor(std::string cityName, std::string neighborName);
    
    //File I/O
    //-Input City Data from Text
    //-Output Paths Data to Text

    //Returns a list of all the possible paths and their distances
    //from a city and back
    std::ostream &printPaths(city_node city);
};

#endif