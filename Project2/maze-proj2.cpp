#include "maze-proj2.h"

Maze::Maze()
{
    this->startLocation = Location();
    this->endLocation = Location();
    this->validLocations = set<Location>();
}

Location Maze::getStartLocation() const
{
    return this->startLocation;
}

bool Maze::isValidLocation(const Location &loc) const
{
    set<Location>::iterator temp;
    temp = this->validLocations.find(loc);
    if (temp != this->validLocations.end())
    {
        return true;
    }
    return false;
}

bool Maze::isEndLocation(const Location &loc) const
{
    if (this->endLocation == loc)
    {
        return true;
    }
    return false;
}

istream &operator>>(istream &is, Maze &m)
{

}