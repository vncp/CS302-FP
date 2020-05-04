/*
Neighbor class which keeps a pointer to a certain city_node to represent the neighbor of the 
object it is a member of. Uses m_miles as the weight or distance and a scaling factor of mpg.
From this, the neighbor class is able to return a cost of travel between cities.
*/

#ifndef _NEIGHBOR_
#define _NEIGHBOR_

class city_node;

class neighbor{
private:
    city_node *m_neighbor;
    float m_miles;
    float m_cost;
public:
    //Parameterized constructor which sets the current calling city node to the neighbor of the 
    //other and vice versa. 
    neighbor(city_node *city, const float distance, const float mpg = 40):
     m_neighbor(city),m_miles(distance), m_cost(distance*mpg)
{
}
    //The cost of the trip between cities which is the distance multiplied by the mpg
    float getCost() const
    {
        return m_cost;
    }
    //The distance between city nodes which is the weight of the edges in the graph
    float getDistance() const
    {
        return m_miles;
    }
    //Returns a city_ndoe pointer to the neighbor of the calling object
    city_node *getNeighbor()
    {
        return m_neighbor;
    }
};
#endif