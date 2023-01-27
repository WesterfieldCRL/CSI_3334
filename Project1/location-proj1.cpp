#include "location-proj1.h"
#include <iostream>

Location::Location()
{
    this->row = 0;
    this->col = 0;
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
        cout << "something went wrong in iterationCurrent" << endl;
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
        cout << "something went wrong in iterationAdvance" << endl;
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

/*
Test Mazes:

10
0 3
1 0
1 1
1 2
1 3
2 0
3 0
3 1
3 2
3 3
0 3
3 3

12
0 2
1 0
1 2
1 4
2 0
2 1
2 2
2 3
2 4
3 0
3 4
4 2
4 2
0 2

9
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
0 0
2 2

7
0 0
0 1
1 0
1 1
1 3
2 0
2 1
0 0
1 3

10
0 1
0 2
0 3
1 1
1 3
2 0
2 1
2 3
3 0
3 3
3 3
3 0

14
0 0
0 1
0 2
0 3
0 4
0 5
1 0
1 5
2 0
2 1
2 2
2 3
2 4
2 5
0 1
0 0

12
0 0
0 1
0 2
0 3
1 0
1 2
1 3
2 0
2 2
3 0
3 1
3 2
0 2
0 0

12
0 0
0 1
0 2
0 3
1 0
1 2
2 0
2 2
3 0
3 1
3 2
3 3
3 2
0 2

10
0 0
0 1
0 2
0 3
1 1
1 2
1 3
2 1
2 2
2 3
0 1
0 0

25
0 0
0 1
0 2
0 3
0 4
1 0
1 1
1 2
1 3
1 4
2 0
2 1
2 2
2 3
2 4
3 0
3 1
3 2
3 3
3 4
4 0
4 1
4 2
4 3
4 4
1 1
1 2

*/