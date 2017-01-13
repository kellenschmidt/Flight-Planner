#ifndef FLIGHTROUTE_H
#define FLIGHTROUTE_H

#include "vector.h"
#include <string>
#include <fstream>

class FlightRoute
{
private:
    Vector<std::string> cities;
    double totalCost;
    double totalTime;

public:
    // Purpose: Set default values for FlightRoute object
    // Parameters: None
    // Return: None
    FlightRoute();

    // Purpose: add a city to the vector
    // Parameters: a string representing the name of the city to be added
    // Return: None
    void addCity(std::string);

    // Purpose: set total cost of flight
    // Parameters: a double representing the total cost of the flight
    // Return: None
    void setTotalCost(double);

    // Purpose: get total cost of flight
    // Parameters: None
    // Return: double representing the total cost of the flight
    double getTotalCost();

    // Purpose: set total time of flight
    // Parameters: a double representing the total time of the flight
    // Return: None
    void setTotalTime(double);

    // Purpose: get total time of flight
    // Parameters: None
    // Return: a double representing the total time of the flight
    double getTotalTime();

    // Purpose: print the path, time, and cost of the flight route
    // Parameters: an integer representing the path number
    //             an ofstream object representing the output file
    // Return: None
    void print(int, std::ofstream &);
};

#endif // FLIGHTROUTE_H
