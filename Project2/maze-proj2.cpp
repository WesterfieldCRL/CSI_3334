/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: maze-proj2.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains all the functions for the Maze class.
 * The functions include the default constructor, the getStartLocation function,
 * the isValidLocation function, the isEndLocation function, and the operator>> function.
 * 
 */

#include "maze-proj2.h"

/**
 * Maze
 * 
 * Constructor for the Maze class. 
 * Sets the startLocation and endLocation to the default Location,
 * and the validLocations to an empty set.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

Maze::Maze(void) {
}

/**
 * getStartLocation
 * 
 * Returns the startLocation of the maze.
 * 
 * Parameters:
 *   none
 * 
 * Return value: the startLocation of the maze
 */

Location Maze::getStartLocation(void) const {
    return this->startLocation;
}

/**
 * isValidLocation
 * 
 * Returns true if the location provided is in the validLocations set.
 * Returns false if the location is not in the validLocations set.
 * 
 * Parameters:
 *   loc - the location to check
 * 
 * Return value: tells the user if the provided location is in
 *               the validLocations set
 */

bool Maze::isValidLocation(const Location &loc) const {
    set<Location>::iterator temp;
    temp = this->validLocations.find(loc);
    if (temp != this->validLocations.end()) {
        return true;
    }
    return false;
}

/**
 * isEndLocation
 * 
 * Returns true if the location provided is equal to the endLocation.
 * Returns false if the location is not equal to the endLocation.
 * 
 * Parameters:
 *   loc - the location to check
 * 
 * Return value: tells the user if the provided location is equal to the endLocation
 */

bool Maze::isEndLocation(const Location &loc) const {
    if (this->endLocation == loc) {
        return true;
    }
    return false;
}

/**
 * operator>>
 * 
 * Overloads the >> operator to read in a maze from an input stream.
 * 
 * Parameters:
 *   is - the input stream to read from
 *   m - the maze to read into
 * 
 * Return value: the input stream to allow for input chaining
 */

istream &operator>>(istream &is, Maze &m) {
    Location temp;
    int num;
    m.validLocations.clear();
    is >> num;

    for (int i = 0; i < num; i++) {
        is >> temp;
        m.validLocations.insert(temp);
    }
    is >> m.startLocation;
    is >> m.endLocation;
    return is;
}