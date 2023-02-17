/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: driver-proj2.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the main function for this program.
 * The main function includes iostream, map, vector, 
 * location-proj2.h, arrayqueue-prof-proj2.h, arrayqueue-student-proj2.h maze-proj12.h
 * 
 * uses namespace std
 * 
 * The main contains the implementation of a simple word melt
 * that finds the shortest path from the start location to the end location
 * by using a breadth first search. This is accomplished by using a queue
 * to store the locations that have been visited and a map to store the
 * locations that have been visited and the location that they came from.
 * The program then outputs the solution if one is found or outputs
 * no solution if one is not found. If there is a solution, the program
 * will use a vector to reverse the order of the locations and output them
 * in the correct order.
 */

#include <iostream>
#include <map>
#include <vector>
#include "location-proj2.h"
#include "maze-proj2.h"
#include "arrayqueue-prof-proj2.h"
#include "arrayqueue-student-proj2.h"

using namespace std;

/**
 * main
 *
 * This function uses the functions provided by the location, queue, and maze classes
 * to solve a inputed word melt maze. The input provided must have the number 
 * of valid locations at the top, and then provide each valid word location.
 * After all the valid locations, the start and end location must be provided.
 * The program then adds the start location to the queue, and then loops through
 * every valid location by using the location class to get the neighbors of the
 * current location. If the end location is found, the program exits the loop
 * and outputs the solution. If no solution is found, the program will say so.
 * 
 * Parameters:
 *   none
 * 
 * Return value: 0 (indicating a successful run)
 */

int main() {
    Maze maze;
    Location location;
    ArrayQueue<Location> queueLoc;
    bool endFound = false;
    vector<Location> printOrder;
    map<Location, Location> map;

    cin >> maze;

    location = maze.getStartLocation();

    queueLoc.add(location);

    if (maze.isEndLocation(location)) {
        endFound = true;
    }

    while (!endFound && queueLoc.getLength() > 0) {
        location = queueLoc.getFront();
        queueLoc.remove();
        location.iterationBegin();
        while (!endFound && !location.iterationDone()) {
            Location temp = location.iterationCurrent();
            if (maze.isEndLocation(temp)) {
                endFound = true;
                map[temp] = location;
                location = temp;
            }
            else if (maze.isValidLocation(temp) && map.find(temp) == map.end()) {
                queueLoc.add(temp);
                map[temp] = location;
            }
            location.iterationAdvance();
        }
    }
    

    if (endFound) {
        cout << "Solution found" << endl;
        for (int i = 0; !(location == maze.getStartLocation()); i++) {
            printOrder.push_back(location);
            location = map[location];
        }
        printOrder.push_back(maze.getStartLocation());

        for (int i = printOrder.size()-1; i >= 0; i--) {
            cout << printOrder[i] << endl;
        }
    }
    else {
        cout << "No solution" << endl;
    }


    return 0;
}