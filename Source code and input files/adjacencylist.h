#ifndef ADJACENCYLIST
#define ADJACENCYLIST

#include "linkedlist.h"
#include "flightdata.h"
#include "node.h"

template <class T>
class AdjacencyList
{
private:
    LinkedList<LinkedList<T>> values;

public:
    // Purpose: Default constructor: Doesn't do anything because there's nothing to initialize
    // Parameters: None
    // Return: None
    AdjacencyList()
    {
        // Do nothing
    }

    // Purpose: insert a flight into the adjacency list
    // Parameters: flightData object representing the flight to be added
    // Return: None
    void insert(FlightData flight)
    {
        // Temporary node used to iterate along linked list
        Node<LinkedList<T>>* curr = values.front;
        // If adjacency list is empty add element at front
        if(values.front == nullptr)
        {
            LinkedList<FlightData> temp;
            temp.push_back(flight);
            values.push_back(temp);
        }

        // If adjacency list is not empty then if origin city is not already in adjacency
        // list add new linked list to adjacenct list. If it is, add flight to end of the
        // linked list for that origin city
        else
        {
            while(curr != nullptr)
            {
                // True when matching origin city is found in adjacency list
                if(curr->data.front->data.getOrigin() == flight.getOrigin())
                {
                    curr->data.push_back(flight);
                    break;
                }
                curr = curr->next;
            }

            // Add new linked list to adjacency list if origin city is not in adjacency list
            if(curr == nullptr)
            {
                LinkedList<FlightData> temp;
                temp.push_back(flight);
                values.push_back(temp);
            }
        }
    }

    // Purpose: get the linked list for a certain city from the adjacency list
    // Parameters: string representing the name of the origin city to get linked list of
    // Return: linked list of FlightData objects for a certain element in adjacency list
    LinkedList<FlightData> getOriginCityList(std::string cityName)
    {
        // Temporary node used to iterate along linked list
        Node<LinkedList<T>>* curr = values.front;
        while(curr != nullptr)
        {
            // True when linked list is found for the input city
            if(curr->data.front->data.getOrigin() == cityName)
            {
                return curr->data;
            }
            curr = curr->next;
        }

        // Return empty object if city isn't in adjacency list
        if(curr == nullptr)
        {
            LinkedList<FlightData> empty;
            return empty;
        }
    }

    // Purpose: Print the adjacency list
    // Parameters: None
    // Return: None
    void print()
    {
        // Temporary node used to iterate along linked list
        Node<LinkedList<T>>* curr = values.front;
        while(curr != nullptr)
        {
            std::cout << curr->data.front->data.getOrigin() << " = ";
            curr->data.print();
            std::cout << "\n";
            curr = curr->next;
        }
    }
};

#endif // ADJACENCYLIST
