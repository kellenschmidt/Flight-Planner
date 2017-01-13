#include "flightroute.h"
#include <iomanip>
#include <fstream>

using namespace std;

FlightRoute::FlightRoute()
{
    totalCost = 0;
    totalTime = 0;
}

void FlightRoute::addCity(string cityName)
{
    cities.push_back(cityName);
}

void FlightRoute::setTotalCost(double tc)
{
    // Only set total cost if it is positive
    if(tc > 0)
        totalCost = tc;
    else
        cerr << "Invalid total cost\n";
}

double FlightRoute::getTotalCost()
{
    return totalCost;
}

void FlightRoute::setTotalTime(double tt)
{
    // Only set total time if it is positive
    if(tt > 0)
        totalTime = tt;
    else
        cerr << "Invalid total time\n";
}

double FlightRoute::getTotalTime()
{
    return totalTime;
}

void FlightRoute::print(int pathNumber, ofstream &outFile)
{
    // Print path number
    outFile << "Path " << pathNumber << ": ";

    // Print each of the cities followed by an arrow except the last city
    for(int i=0; i<cities.getSize()-1; i++)
    {
        outFile << cities[i] << " -> ";
    }

    // Print the last city followed by a period then the time and cost (with 2 decimals)
    outFile << cities[cities.getSize()-1] << ". Time: " << fixed << setprecision(0)
         << totalTime << " Cost: " << fixed << setprecision(2) << totalCost << "\n";
}
