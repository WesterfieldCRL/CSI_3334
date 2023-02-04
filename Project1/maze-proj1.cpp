/* CSI 3334
 * Project 1 -- Two-dimensional Maze Solver
 * Filename: maze-proj1.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the implementation of all functions defined in maze-proj1.cpp.
 * Includes a constructor for Maze, a destructor, a way of getting the Location
 * object stored in startLocation, a check to see if a provided Location object is
 * stored in the validLocations array, a check if the provided Location object is equal
 * to the Location object stored in endLocation, and a way of getting input from the user
 * to fill out Maze's array of valid locations.
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
 * Return value: the start Location of the maze
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
 *   loc: the object that is getting checked to see if it is in the array
 * 
 * Return value: tells the user if the provided object is in the array
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
 *   loc: The object being compared to the end location
 * 
 * Return value: tells the user if the provided location is equal to the end location
 * of the maze
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
 *   is: the stream to get input from
 *   m: the object that is being filled with input
 * 
 * Return value: the given istream to permit output chaining
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