#include "flightplanner.h"
#include "adjacencylist.h"
#include "flightroute.h"
#include "flightdata.h"
#include "flightplan.h"
#include "linkedlist.h"
#include "vector.h"
#include "stack.h"
#include "node.h"
#include <iostream>
#include <string>

using namespace std;

FlightPlanner::FlightPlanner()
{
    flightNumber = 1;
}

void FlightPlanner::readFlightData(string fileName)
{
    inFlightData.open(fileName);
    // Verify that file was opened correctly
    if(!inFlightData)
    {
        cerr << "Flight Data file not opened correctly";
        exit(EXIT_FAILURE);
    }

    // Read in the number of tokens
    string line;
    getline(inFlightData, line);
    int numTokens = stoi(line);

    string origin, destination;
    double cost, time;
    // Loop through each token/line of the file
    for(int i=0; i<numTokens; i++)
    {
        getline(inFlightData, origin, '|');
        getline(inFlightData, destination, '|');
        getline(inFlightData, line, '|');
        // stoi() converts string to number
        cost = stoi(line);
        getline(inFlightData, line, '\n');
        time = stoi(line);
        // Insert flight in the original direction
        FlightData forward(origin, destination, cost, time);
        flights.insert(forward);
        // Insert flight in the reverse direction
        FlightData backward(destination, origin, cost, time);
        flights.insert(backward);
    }
}

void FlightPlanner::readFlightPlans(string fileName)
{
    inFlightPlans.open(fileName);
    // Verify that file was opened correctly
    if(!inFlightPlans)
    {
        cerr << "Flight Plans file not opened correctly";
        exit(EXIT_FAILURE);
    }

    // Read in the number of tokens
    string line;
    getline(inFlightPlans, line);
    int numTokens = stoi(line);

    string origin, destination, sortType;
    // Loop through each token/line of the file
    for(int i=0; i<numTokens; i++)
    {
        getline(inFlightPlans, origin, '|');
        getline(inFlightPlans, destination, '|');
        getline(inFlightPlans, sortType, '\n');
        // If newline character is captured then remove
        if(sortType.length() > 1) {
            sortType = sortType[0];
        }
        // Create FlightPlan object from for the data
        FlightPlan fp(origin, destination, sortType);
        // Perform iterative backtracking to find routes
        Vector<Stack<Node<FlightData>*>> currStacks = findRoutes(fp);
        // Reinterpret output into simpler form
        Vector<FlightRoute> currentRoute = translateRoutes(currStacks);
        // Sort routes based on sort type and reduce to top 3
        currentRoute = sortRoutes(currentRoute, sortType);
        // Write result to the file
        outputRoute(currentRoute, fp);
    }
}

Vector<Stack<Node<FlightData>*>> FlightPlanner::findRoutes(FlightPlan plan)
{
    // Vector of the stacks of curr pointers for each route
    Vector<Stack<Node<FlightData>*>> currStacks;
    // Stack of linked lists for each city along route
    Stack<LinkedList<FlightData>> routeStack;
    // Add first linked list of destinations to routeStack
    routeStack.push(flights.getOriginCityList(plan.getOrigin()));
    // Stack of pointers to the current nodes in each linked list
    Stack<Node<FlightData>*> currs;
    // Pointer to current FlightData node being tested
    Node<FlightData> *curr = routeStack.getTop().front;

    do{        
        // Reached end of current linked list, no more destinations from current origin city
        // Pop stack to previous origin city and try next destination
        if(curr == nullptr)
        {
            bool allRoutesFound = false;

            // Loop until curr is not nullptr
            while(curr == nullptr)
            {
                // Pop current linked list of destinations
                routeStack.pop();

                // Stack is empty so all routes have been tested
                if(routeStack.isEmpty())
                {
                    allRoutesFound = true;
                    break;
                }

                // Pop current pointer to node of FlightData and
                // make the value that was popped the current pointer
                curr = currs.pop();
                // Move to next destination in same linked list
                curr = curr->next;
                // Skip cities that have already been visited
                while(curr != nullptr && isCityOnStack(currs, curr->data.getDestination()))
                {
                    curr = curr->next;
                }
            }
            // Used to break out of nested loops
            if(allRoutesFound)
                break;
        }

        // Route found, add stack of linked lists and curr pointer to their respective
        // vectors then continue searching to find another route
        if(curr->data.getDestination() == plan.getDestination())
        {
            // Add curr pointer to stack of curr pointers
            currs.push(curr);
            // Add stack of curr pointers to the vector of stacks of curr pointers
            currStacks.push_back(currs);

            currs.pop();
            // Move to next destination in same linked list
            curr = curr->next;
            // Skip cities that have already been visited
            while(curr != nullptr && isCityOnStack(currs, curr->data.getDestination()))
            {
                curr = curr->next;
            }
        }

        // Add new linked list to stack if possible
        if(curr != nullptr)
        {
            // Add curr pointer to stack of curr pointers
            currs.push(curr);

            // Add linked list of destinations being tested to stack
            routeStack.push(flights.getOriginCityList(curr->data.getDestination()));
            // Set curr pointer to the front of the latest linked list
            curr = routeStack.getTop().front;

            // Skip cities that have already been visited
            while(curr != nullptr && isCityOnStack(currs, curr->data.getDestination()))
            {
                curr = curr->next;
            }
        }

    // Loop until break is hit
    }while(true);

    return currStacks;
}

bool FlightPlanner::isCityOnStack(Stack<Node<FlightData>*> stack, string city)
{
    Node<FlightData>* top = nullptr;
    // Loop until stack is empty
    while(!stack.isEmpty())
    {
        top = stack.pop();
        // If origin or destination cities of popped node equal city in question return true
        if(top->data.getOrigin() == city || top->data.getDestination() == city)
            return true;
    }
    // If city is not on stack, return false
    return false;
}

Vector<FlightRoute> FlightPlanner::translateRoutes(Vector<Stack<Node<FlightData>*>> currStacks)
{
    // The reversed stack
    Stack<FlightData> flightStack;
    // The vector to be returned
    Vector<FlightRoute> flightRouteVect;

    // Loop through each stack in the vector of stacks
    for(int i=0; i < currStacks.getSize(); i++)
    {
        // Reverse stack
        while(!currStacks[i].isEmpty())
        {
            Node<FlightData>* current = currStacks[i].pop();
            flightStack.push(current->data);
        }

        // Create object to store flight route
        FlightRoute flightRoute;
        int timeSum = 0;
        int costSum = 0;
        // Add origin and destination city the first time
        FlightData flight = flightStack.pop();
        flightRoute.addCity(flight.getOrigin());
        flightRoute.addCity(flight.getDestination());
        costSum += flight.getCost();
        timeSum += flight.getTime();

        // Add cities along route to FlightRoute object and sum the time and cost of the route
        while(!flightStack.isEmpty())
        {
            flight = flightStack.pop();
            flightRoute.addCity(flight.getDestination());
            costSum += flight.getCost();
            timeSum += flight.getTime();
        }

        // Put the final time and cost sums into the FlightRoute object
        flightRoute.setTotalCost(costSum);
        flightRoute.setTotalTime(timeSum);

        // Add the FlightRoute to the vector of flight routes
        flightRouteVect.push_back(flightRoute);
    }
    return flightRouteVect;
}

Vector<FlightRoute> FlightPlanner::sortRoutes(Vector<FlightRoute> routeVect, string sortType)
{
    Vector<FlightRoute> flightRouteVect;
    // Sort based on time
    if(sortType == "T")
    {
        // Selection sort all FlightRoutes
        int minIndex;
        for(int i=0; i<routeVect.getSize()-1; i++)
        {
            minIndex = i;
            for(int j=i+1; j<routeVect.getSize(); j++)
            {
                if(routeVect[j].getTotalTime() < routeVect[minIndex].getTotalTime())
                    minIndex = j;
            }
            if(minIndex != i)
            {
                FlightRoute temp = routeVect[i];
                routeVect[i] = routeVect[minIndex];
                routeVect[minIndex] = temp;
            }
        }
    }
    // Sort based on cost
    else
    {
        // Selection sort all FlightRoutes
        int minIndex;
        for(int i=0; i<routeVect.getSize()-1; i++)
        {
            minIndex = i;
            for(int j=i+1; j<routeVect.getSize(); j++)
            {
                if(routeVect[j].getTotalCost() < routeVect[minIndex].getTotalCost())
                    minIndex = j;
            }
            if(minIndex != i)
            {
                FlightRoute temp = routeVect[i];
                routeVect[i] = routeVect[minIndex];
                routeVect[minIndex] = temp;
            }
        }
    }
    // Cut vector down to only top 3
    for(int k=0; k<3 && k<routeVect.getSize(); k++)
    {
        flightRouteVect.push_back(routeVect[k]);
    }
    return flightRouteVect;
}

void FlightPlanner::outputRoute(Vector<FlightRoute> routeVect, FlightPlan plan)
{
    // Output the title line for the flight
    outFlightInfo << "Flight " << flightNumber << ": " << plan.getOrigin() << ", " << plan.getDestination();
    if(plan.getSortType() == "T")
        outFlightInfo << " (Time)\n";
    else
        outFlightInfo << " (Cost)\n";

    // Output each of the paths
    for(int i=0; i<routeVect.getSize(); i++)
    {
        routeVect[i].print(i+1, outFlightInfo);
    }

    // Output error of no path exists
    if(routeVect.getSize() == 0)
    {
        outFlightInfo << "No routes found.\n";
    }
    outFlightInfo << "\n";

    // Increment flight number
    flightNumber++;
}


void FlightPlanner::openOutputFile(std::string fileName)
{
    outFlightInfo.open(fileName);
    // Verify that file was opened correctly
    if(!outFlightInfo)
    {
        cerr << "Output file not opened correctly";
        exit(EXIT_FAILURE);
    }
}

void FlightPlanner::closeFiles()
{
    inFlightData.close();
    inFlightPlans.close();
    outFlightInfo.close();
}
