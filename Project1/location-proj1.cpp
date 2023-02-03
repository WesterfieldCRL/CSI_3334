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
 * Return value: Location
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
 * Return value: boolean
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
 *   loc: const Location passed by reference
 * 
 * Return value: boolean
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
 *   loc: const Location passed by reference
 * 
 * Return value: ostream
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
 *   loc: cpmst Location passed by reference
 * 
 * Return value: none
 */
istream &operator>>(istream &is, Location &loc) {
    is >> loc.row >> loc.col;
    return is;
}