#ifndef FLIGHTPLAN_H
#define FLIGHTPLAN_H

#include <string>

class FlightPlan
{
private:
    std::string origin;
    std::string destination;
    std::string sortType;

public:
    // Purpose: initialize values of FlightPlan object
    // Parameters: string representing name of origin city
    //             string representing name of destination city
    //             string representing the sort type (C or T)
    // Return: None
    FlightPlan(std::string, std::string, std::string);

    // Purpose: get origin city name
    // Parameters: None
    // Return: string representing name of origin city
    std::string getOrigin();

    // Purpose: set origin city name
    // Parameters: string representing name of origin city
    // Return: None
    void setOrigin(std::string);

    // Purpose: get destination city name
    // Parameters: None
    // Return: string representing name of destination city
    std::string getDestination();

    // Purpose: set destination city name
    // Parameters: string representing name of destination city
    // Return: None
    void setDestination(std::string);

    // Purpose: get sort type
    // Parameters: None
    // Return: string representing the sort type
    std::string getSortType();

    // Purpose: verify that sort type is valid then set sort type
    // Parameters: string representing the sort type (C or T)
    // Return: None
    void setSortType(std::string);
};

#endif // FLIGHTPLAN_H
