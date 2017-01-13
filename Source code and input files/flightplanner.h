#ifndef FLIGHTPLANNER_H
#define FLIGHTPLANNER_H

#include "linkedlist.h"
#include "adjacencylist.h"
#include "flightroute.h"
#include "flightdata.h"
#include "flightplan.h"
#include "vector.h"
#include "stack.h"
#include <fstream>


class FlightPlanner
{
private:
    std::ifstream inFlightData;
    std::ifstream inFlightPlans;
    std::ofstream outFlightInfo;
    AdjacencyList<FlightData> flights;
    int flightNumber;

    // Purpose: Performs iterative backtracking to find all routes
    // Parameters: FlightData object to find route for
    // Return: A vector containing a stack of all the pointers to nodes of
    // FlightData objects created during the iterative backtracking
    Vector<Stack<Node<FlightData>*>> findRoutes(FlightPlan);

    // Purpose: determines if a string matches the city or destination of
    // any FlightData object on a stack
    // Parameters: a stack of pointers to nodes of FlightData objects to search for string in
    //             string representing the city to search for
    // Return: bool representing whether the city was found on the stack or not
    bool isCityOnStack(Stack<Node<FlightData>*>, std::string);

    // Purpose: reverses the stack and then interprets its data puting the important
    // data in a FlightRoute object for each flight route in the vector
    // Parameters: a vector of stacks of pointers to nodes of FlightData
    // Return: a vector of FlightRoute objects containing all of the possible flight routes
    Vector<FlightRoute> translateRoutes(Vector<Stack<Node<FlightData>*>>);

    // Purpose: sort all of the possible routes according to their sort type and save top 3
    // Parameters: a vector of FlightRoute objects containing all of the possible routes
    //             string representing the sort type
    // Return: an updated version of the vector of FlightRoute objects passed to the function
    Vector<FlightRoute> sortRoutes(Vector<FlightRoute>, std::string);

    // Purpose: write to the output file the flights and their routes
    // Parameters: a vector of FlightRoute objects containing the possible routes
    //             a FlightPlan object representing the current flight plan
    // Return: None
    void outputRoute(Vector<FlightRoute>, FlightPlan);

public:
    // Purpose: Set default values for flightData object
    // Parameters: None
    // Return: None
    FlightPlanner();

    // Purpose: open and read the file containing the list of possible flights
    // Parameters: string representing the name of the file to be opened
    // Return: None
    void readFlightData(std::string);

    // Purpose: open and read the file containing the list of flights to find routes for
    // Parameters: string representing the name of the file to be opened
    // Return: None
    void readFlightPlans(std::string);

    // Purpose: open the file to output the results to
    // Parameters: string representing the name of the file to output to
    // Return: None
    void openOutputFile(std::string);

    // Purpose: close all three i/o files
    // Parameters: None
    // Return: None
    void closeFiles();
};

#endif // FLIGHTPLANNER_H
