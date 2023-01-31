#include "maze-proj1.h"
#include <iostream>

Maze::Maze()
{
    this->validLocationCount = 0;
    this->validLocations = NULL;
    this->startLocation = Location();
    this->endLocation = Location();
}

Maze::~Maze()
{
    if (this->validLocations != NULL)
    {
        delete this->validLocations;
    }
    this->validLocations = NULL;
    this->validLocationCount = 0;
}

Location Maze::getStartLocation(void) const
{
    return this->startLocation;
}

bool Maze::isValidLocation(const Location &loc) const
{
    for (int i = 0; i < this->validLocationCount; i++)
    {
        if (this->validLocations[i] == loc)
        {
            return true;
        }
    }
    return false;
}

bool Maze::isEndLocation(const Location &loc) const
{
    if (loc == this->endLocation)
    {
        return true;
    }
    return false;
}

istream &operator>>(istream &is, Maze &m)
{
    int dataNum;
    is >> dataNum;
    Location temp;
    m.validLocationCount = dataNum;
    delete m.validLocations;
    m.validLocations = new Location[m.validLocationCount];

    for (int i = 0; i < dataNum; i++)
    {
        is >> temp;
        m.validLocations[i] = temp;
    }

    is >> temp;
    m.startLocation = temp;
    is >> temp;
    m.endLocation = temp;

    return is;
}