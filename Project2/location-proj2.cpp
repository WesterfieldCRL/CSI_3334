#include "location-proj2.h"

Location::Location()
{
    this->word = "default";
    this->nextLetter = 'a';
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
}

void Location::iterationBegin()
{
    this->nextLetter = 'a';
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
}

Location Location::iterationCurrent() const
{

}
void Location::iterationAdvance()
{

}

bool Location::iterationDone() const
{
    if (this->iterationMode == DONE)
    {
        return true;
    }
    return false;
}

bool Location::operator==(const Location &loc) const
{
    if (this->word == loc.word)
    {
        return true;
    }
    return false;
}

ostream &operator<<(ostream &os, const Location &loc)
{
    
}

istream &operator>>(istream &is, Location &loc)
{

}

bool Location::operator<(const Location &loc) const
{

}