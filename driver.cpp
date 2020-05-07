#include "Cities.h"
#include <fstream>
#include <iostream>
using namespace std;

const string IN_FILENAME = "city_input.csv";
const string OUT_FILENAME = "output.txt";

int main(void)
{
    cout << "Final Project - Traveling Salesman Problem - CS302 - Erin Keith\n";
    cout << "Group: Vincent Pham & Prim Wandeevong\n\n";
    cout << "https://github.com/vncp/CS302-FP\n\n";

    //Testing File IO + addCity() + addNeighbor()
    Cities city_graph;
    ifstream inFile;
    inFile.open(IN_FILENAME);
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
    cout << "Creating edges between vertices with the following weights: \n";
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
    inFile.close();
    cout << endl;

    //Output to Terminal
    ofstream outputStream;
    outputStream.open(OUT_FILENAME);
    cout << "Calculating all paths and minimum cost..\n";
    city_graph.printPaths(outputStream);
    cout << "\nPrinting Data to " << OUT_FILENAME << endl;
    outputStream.close();
}