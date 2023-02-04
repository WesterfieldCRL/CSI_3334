/* CSI 3334
 * Project 1 -- Two-dimensional Maze Solver
 * Filename: driver-proj1.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the main function for this program.
 * The main function includes iostream, location-proj1.h, stack-proj1.h, and maze-proj1.h
 * uses namespace std
 * The main contains the implementation of a simple maze solver.
 * It assumes that the input is valid, and it takes that input and creates
 * a stack of valid locations. A start and end location is also gotten from input.
 * The program loops through each location in a specific order, and once an order
 * is found the program exits and outputs the found solution. If no order is found,
 * the program tell that to the user.
 */

#include "location-proj1.h"
#include "stack-proj1.h"
#include "maze-proj1.h"
#include <iostream>

using namespace std;

/**
 * main
 *
 * This function uses the functions provided by the location, stack, and maze classes
 * to solve a inputed maze. The input provided must have the number of valid locations
 * at the top, and then provide all of those locations in row col format, followed
 * by the start and end location. The function pushes the start location on the stack,
 * and then checks every path from the start location around the maze. It searches
 * by checking right, down, left, and up. If a solution is found, the function prints
 * the contents of the stack which contains all the locations traversed to get to the
 * end location. If no solution is found, the program will say so.
 * 
 * Parameters:
 *   none
 * 
 * Return value: 0 (indicating a successful run)
 */

int main() {
    Maze maze;
    Location m;
    Location neighbor;
    LocationStack stack;
    bool NoSolution = false;

    cin >> maze;

    m = maze.getStartLocation();
    m.iterationBegin();
    stack.push(m);

    while (!NoSolution && !maze.isEndLocation(stack.getTop())) {
        m = stack.getTop();
        stack.pop();
        if (!m.iterationDone()) {
            neighbor = m.iterationCurrent();
            neighbor.iterationBegin();
            m.iterationAdvance();
            stack.push(m);
            if (!stack.isOn(neighbor) && maze.isValidLocation(neighbor)) {
                stack.push(neighbor);
            }
            //cout << stack << endl << endl;
            //cout << "n = " << neighbor << endl;
        }
        else if (stack.isEmpty()) {
            NoSolution = true;
        }
    }

    if (!NoSolution) {
        cout << "Solution found" << endl;
        cout << stack;
    }
    else {
        cout << "No solution" << endl;
    }


    return 0;
}

