/* CSI 3334
 * Project 1 -- Two-dimensional Maze Solver
 * Filename: location-proj1.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the implementation of all functions defined in location-proj1.h.
 * This includes the implementation of all of the functions used in the Location class
 * This includes a constructor that sets row and col to 0, and nextDirection to the
 * RIGHT enum value. This also includes a function iterationBegin for starting the
 * iteration over the enum values stored in nextDirection. The function sets nextDirection
 * equal to RIGHT. The function iterationBegin returns the neighbor of the current Location
 * based on what nextDirection is set to. iterationAdvance sets nextDirection to the next
 * enum value, and iterationDone returns true if nextDirection is set to DONE. The operator==
 * function checks if the provided Location's row and col values are equal to this
 * objects row and col values. The friend function operator>> allows for inputting
 * values into row and col, and operator<< prints row and col to the ostream provided.
 * 
 */

#include "location-proj1.h"
#include <iostream>

/**
 * Location
 * 
 * Constructor for the Location class.
 * Sets row and col to 0
 * sets nextDirection to RIGHT
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */
Location::Location() {
    this->row = 0;
    this->col = 0;
    this->nextDirection = RIGHT;
}

/**
 * iterationBegin
 * 
 * sets nextDirection to RIGHT
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */
void Location::iterationBegin() {
    this->nextDirection = RIGHT;
}

/**
 * iterationCurrent
 * 
 * returns the neighbor dictated by nextDirection
 * if right, returns a location shifted right by 1
 * if down returns a location shifted down by 1
 * if left returns a location shifted left by 1
 * if up returns a location shifted up by 1
 * 
 * Parameters:
 *   none
 * 
 * Return value: the neighbor of the current location dictated by nextDirection
 */
Location Location::iterationCurrent() const {
    Location returnLoc = *this;
    switch (this->nextDirection) {
    case RIGHT:
        returnLoc.col++;
        break;
    case DOWN:
        returnLoc.row++;
        break;
    case LEFT:
        returnLoc.col--;
        break;
    case UP:
        returnLoc.row--;
        break;
    default:
        //cout << "something went wrong in iterationCurrent" << endl;
        break;
    }

    return returnLoc;
}

/**
 * iterationAdvance
 * 
 * increases the nextDirection
 * if right increases to down,
 * if down increases to left,
 * if left increases to up
 * if up increases to done
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */
void Location::iterationAdvance() {
    switch (this->nextDirection) {
    case RIGHT:
        this->nextDirection = DOWN;
        break;
    case DOWN:
        this->nextDirection = LEFT;
        break;
    case LEFT:
        this->nextDirection = UP;
        break;
    case UP:
        this->nextDirection = DONE;
        break;
    default:
        //cout << "something went wrong in iterationAdvance" << endl;
        break;
    }
}

/**
 * iterationDone
 * 
 * if nextDirection is equal to DONE
 * returns true, otherwise returns false
 * 
 * Parameters:
 *   none
 * 
 * Return value: A boolean to tell the user if iteration has finished over this location
 */
bool Location::iterationDone() const {
    if (this->nextDirection == DONE) {
        return true;
    }
    return false;
}

/**
 * operator==
 * 
 * checks to see if the provided Location object
 * has the same values for row and col as this object
 * if it does, returns true, otherwise returns false
 * 
 * Parameters:
 *   loc: The object to be compared with this object
 * 
 * Return value: A boolean to tell the user if the two Locations are equal
 */
bool Location::operator==(const Location &loc) const {
    if (this->row == loc.row && this->col == loc.col) {
        return true;
    }
    return false;
}

/**
 * operator<<
 * 
 * outputs the row and col of this to the provided ostream
 * 
 * Parameters:
 *   os: ostream to output the values to
 *   loc: where the values to output are coming from
 * 
 * Return value: the given stream to permit output chaining
 */
ostream &operator<<(ostream &os, const Location &loc) {
    os << loc.row << " " << loc.col;
    return os;
}

/**
 * operator>>
 * 
 * takes input from the provided istream to set row and col to the provided values
 * 
 * Parameters:
 *   is: istream, where the input comes from
 *   loc: where the values are being input into
 * 
 * Return value: the given stream to permit output chaining
 */
istream &operator>>(istream &is, Location &loc) {
    is >> loc.row >> loc.col;
    return is;
}