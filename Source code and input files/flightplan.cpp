#include "flightplan.h"
#include <iostream>

using namespace std;

FlightPlan::FlightPlan(string o, string d, string st)
{
    setOrigin(o);
    setDestination(d);
    setSortType(st);
}

string FlightPlan::getOrigin()
{
    return origin;
}

void FlightPlan::setOrigin(string o)
{
    origin = o;
}

string FlightPlan::getDestination()
{
    return destination;
}

void FlightPlan::setDestination(string d)
{
    destination = d;
}

string FlightPlan::getSortType()
{
    return sortType;
}

void FlightPlan::setSortType(string st)
{
    // Only set sort type if it is either C or T
    if(st == "C" || st == "T")
        sortType = st;
    else
        cerr << "Error: Invalid sort type\n";
}

