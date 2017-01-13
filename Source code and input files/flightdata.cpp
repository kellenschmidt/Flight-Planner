#include "flightdata.h"
#include <iostream>
#include <string>

using namespace std;

FlightData::FlightData()
{
    setOrigin("");
    setDestination("");
    setCost(1);
    setTime(1);
}

FlightData::FlightData(std::string o, std::string d, double c, double t)
{
    setOrigin(o);
    setDestination(d);
    setCost(c);
    setTime(t);
}

std::string FlightData::getOrigin()
{
    return origin;
}

void FlightData::setOrigin(std::string o)
{
    origin = o;
}

std::string FlightData::getDestination()
{
    return destination;
}

void FlightData::setDestination(std::string d)
{
    destination = d;
}

double FlightData::getCost()
{
    return cost;
}

void FlightData::setCost(double c)
{
    // Only set cost if it is positive
    if(c >= 0)
        cost = c;
    else
        cerr << "Error: Invalid cost\n";
}

double FlightData::getTime()
{
    return time;
}

void FlightData::setTime(double t)
{
    // Only set time if it is positive
    if(t > 0)
        time = t;
    else
        cerr << "Error: Invalid time\n";
}

FlightData& FlightData::operator=(const FlightData &arg)
{
    setOrigin(arg.origin);
    setDestination(arg.destination);
    setCost(arg.cost);
    setTime(arg.time);
    return *this;
}

FlightData::FlightData(const FlightData &arg)
{
    *this = arg;
}
