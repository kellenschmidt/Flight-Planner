#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

#include <string>

class FlightData
{
private:
    std::string origin;
    std::string destination;
    double cost;
    double time;

public:
    // Purpose: Set default values for FlightData object
    // Parameters: None
    // Return: None
    FlightData();

    // Purpose: initialize values of FlightData object
    // Parameters: string representing name of origin city
    //             string representing name of destination city
    //             double representing flight cost
    //             double representing flight time
    // Return: None
    FlightData(std::string, std::string, double, double);

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

    // Purpose: get flight cost
    // Parameters: None
    // Return: double representing flight cost
    double getCost();

    // Purpose: set flight cost
    // Parameters: double representing flight cost
    // Return: None
    void setCost(double);

    // Purpose: get flight time
    // Parameters: None
    // Return: double representing flight time
    double getTime();

    // Purpose: set flight time
    // Parameters: double representing flight time
    // Return: None
    void setTime(double);

    // Purpose: define how to assign one flightData object to another
    // Parameters: flightData object to assign from
    // Return: current flightData object
    FlightData& operator=(const FlightData &);

    // Purpose: define how to construct one flightData object using another
    // Parameters: flightData object to copy
    // Return: None
    FlightData(const FlightData &);
};

#endif // FLIGHTDATA_H
