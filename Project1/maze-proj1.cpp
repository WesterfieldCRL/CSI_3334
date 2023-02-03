/* CSI 3334
 * Project 1 -- Two-dimensional Maze Solver
 * Filename: maze-proj1.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the implementation of all functions defined in maze-proj1.cpp.
 * 
 * 
 */

#include "maze-proj1.h"
#include <iostream>

/**
 * Maze
 * 
 * constructor for the Maze class
 * sets the validLocationCount to 0
 * sets validLocations to NULL
 * sets the start and end Location to the default location
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */
Maze::Maze() {
    this->validLocationCount = 0;
    this->validLocations = NULL;
    this->startLocation = Location();
    this->endLocation = Location();
}

/**
 * ~Maze
 * 
 * deletes the validLocations pointer
 * sets validLocations to NULL
 * sets validLocationCount to 0
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */
Maze::~Maze() {
    delete [] this->validLocations;
}

/**
 * getStartLocation
 * 
 * returns the Location stored by startLocation
 * 
 * Parameters:
 *   none
 * 
 * Return value: Location
 */
Location Maze::getStartLocation(void) const {
    return this->startLocation;
}

/**
 * isValidLocation
 * 
 * checks to see if the provided location is in the array validLocations
 * if it is in the array, returns true, else returns false
 * 
 * Parameters:
 *   loc: const Location passed by reference
 * 
 * Return value: boolean
 */
bool Maze::isValidLocation(const Location &loc) const {
    for (int i = 0; i < this->validLocationCount; i++) {
        if (this->validLocations[i] == loc) {
            return true;
        }
    }
    return false;
}

/**
 * isEndLocation
 * 
 * checks to see if the provided location is equal to
 * the Location stored by endLocation
 * if it is, returns true, otherwise false
 * 
 * Parameters:
 *   loc: const Location passed by reference
 * 
 * Return value: boolean
 */
bool Maze::isEndLocation(const Location &loc) const {
    if (loc == this->endLocation) {
        return true;
    }
    return false;
}

/**
 * operator>>
 * 
 * takes the input from the provided istream
 * and uses it to fill out the array with valid locations.
 * 
 * Parameters:
 *   is: istream, where the input comes from
 *   m: the Maze object to fill out
 * 
 * Return value: istream
 */
istream &operator>>(istream &is, Maze &m) {
    int dataNum;
    is >> dataNum;
    Location temp;
    m.validLocationCount = dataNum;
    delete [] m.validLocations;
    m.validLocations = new Location[m.validLocationCount];

    for (int i = 0; i < dataNum; i++) {
        is >> temp;
        m.validLocations[i] = temp;
    }

    is >> temp;
    m.startLocation = temp;
    is >> temp;
    m.endLocation = temp;

    return is;
}