#include "location-proj1.h"
#include <iostream>

Location::Location()
{
    this->row = 0;
    this->col = 0;
    this->nextDirection = RIGHT;
}

void Location::iterationBegin()
{
    this->nextDirection = RIGHT;
}

Location Location::iterationCurrent() const
{
    Location returnLoc = *this;
    switch (this->nextDirection)
    {
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
void Location::iterationAdvance()
{
    switch (this->nextDirection)
    {
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

bool Location::iterationDone() const
{
    if (this->nextDirection == DONE)
    {
        return true;
    }
    return false;
}

bool Location::operator==(const Location &loc) const
{
    if (this->row == loc.row && this->col == loc.col)
    {
        return true;
    }
    return false;
}

ostream &operator<<(ostream &os, const Location &loc)
{
    os << loc.row << " " << loc.col;
    return os;
}

istream &operator>>(istream &is, Location &loc)
{
    is >> loc.row >> loc.col;
    return is;
}