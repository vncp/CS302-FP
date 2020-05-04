#include "neighbor.h"
#include "city_node.h"

#include <iostream>

using namespace std;

int main(void)
{
    //Testinc constructors
    city_node city_01("Las Vegas");
    city_node city_02("Reno");
    city_node city_03("San Francisco");
    cout << "Successfully created cities using P-CTOR\n";
    //Testing neighbor/edge creation
    city_01.addNeighbor(city_02, 438.6);
    //Testing getters 
    cout << city_01.getName() << "'s neighbor is " << city_01.getNeighbor()->getName() << endl;
    cout << city_02.getName() << "'s neighbor is " << city_02.getNeighbor()->getName() << endl;

}