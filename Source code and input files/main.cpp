#include <iostream>
#include "flightplanner.h"

using namespace std;

int main(int argc, char* argv[])
{
    FlightPlanner plan;
    plan.readFlightData(argv[1]);
    plan.openOutputFile(argv[3]);
    plan.readFlightPlans(argv[2]);
    plan.closeFiles();
}
