#include "Cities.h"
#include <fstream>
#include <iostream>
using namespace std;

const string FILENAME = "city_input.csv";
int main(void)
{
    cout << "\n";
    //Testing File IO + addCity() + addNeighbor()
    Cities city_graph;
    ifstream inFile;
    inFile.open(FILENAME);
    string temp;

    //Reads cities
    for(int i = 0; i < 5; i++)
    {
        getline(inFile,temp, ',');
        city_graph.addCity(temp);
    }
    getline(inFile,temp);           //Gross fix for last city
    city_graph.addCity(temp);

    //Adds Neighbors
    for(int i = 0; i < 9; i++)
    {
        string city, neighbor, tempD;
        getline(inFile,city, ',');
        getline(inFile,neighbor, ',');
        getline(inFile,tempD);
        float distance = atoi(tempD.c_str());
        cout << city << " " << neighbor << " " << distance << endl;
        if(city_graph.addNeighbor(city,neighbor,distance)==false)
            cout << "Adding Neighbor Failed!\n";
        
    }
    cout << endl;
    city_graph.printData();
    city_graph.printPaths(cout);
}