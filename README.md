# Flight-Planner
Text file based C++ program to compute and organize all possible flight plans for a person wishing to travel between two different cities. Aditionally, it calculates the total cost and time for all parts of each route.

### Implementation Details
* **Adjacency List** - The program stores the structure representing flights with a simple adjacency list data structure. The adjacency list is implemented as a linked list of linked lists. There is one linked list for every distinct city. Each list contains the cities (and other needed info) that can be reached from this city.

* **Iterative Backtracking** - To perform the exhaustive search of flights the program uses an iterative backtracking algorithm (using a stack).

* **Custom Container Classes** - The program does not use any of the STL container classes. Instead, it uses linkled list and stack classes which have been implemented from scratch.

## Instructions
### Input Files
Two different input files are used in order to calculate the trip plan, cost, and time. 

1. **Origination and Destination Data** – This file will contain a sequence of city pairs representing different legs of flights that can be considered in preparing a flight plan. For each leg, the file will also contain a dollar cost for that leg and a time to travel. For each pair in the file, you can assume that it is possible to fly both directions.
```
4
Dallas|Austin|98|47
Austin|Houston|95|39
Dallas|Houston|101|51
Austin|Chicago|144|192
```
The first line of the file will contain an integer indicating how many rows of data will be in the file. Each subsequent row will contain two city names, the cost of the flight, and the number of minutes of the flight. Each field will be separated with a pipe.



2. **Requested Flights** – This file will contain a sequence of origin/destination city pairs. For each pair, the program determines if the flight is or is not possible. If it is possible, it will output to a file the flight plan with the total cost for the flight. If it is not possible, then an error message will be written to the output file.
```
2
Dallas|Houston|T
Chicago|Dallas|C
```
The first line will contain an integer indicating the number of flight plans requested. The subsequent lines will contain a pipe delimited list of city pairs with a trailing character to indicate sorting the output of flights by time (T) or cost (C). The program will find all flight paths between these two cities (if any exists) and calculate the total cost of the flights and the total time in the air.
  
The names of the two input files as well as the output file will be provided via command line arguments.

### Output File
For each flight in the Requested Flight Plans file, the program will print the three most efficient flight plans available based on whether the request was to order by time or cost. If there are fewer than three possible plans, it will output all of the possible plans. If no flight plan can be created, then an error message will be output.
```
Flight 1: Dallas, Houston (Time)
Path 1: Dallas ‐> Houston. Time: 51 Cost: 101.00
Path 2: Dallas ‐> Austin ‐> Houston. Time: 86 Cost: 193.00
Flight 2: Chicago, Dallas (Cost)
Path 1: Chicago ‐> Austin ‐> Dallas. Time: 239 Cost: 242.00
Path 2: Chicago ‐> Austin ‐> Houston ‐> Dallas. Time: 282 Cost: 340.00
```

### Executing the program
Compile the code and generate the executable from the command line
```
g++ *.cpp -std=c++11 -o flightPlan
```
Run the program from the command line with the following arguments
```
./flightPlan <FlightDataFile> <PathsToCalculateFile> <OutputFile>
```
