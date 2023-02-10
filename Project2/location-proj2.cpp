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
    if (this->word[0] == 'a')
    {
        this->nextLetter++;
    }
}

Location Location::iterationCurrent() const
{
    Location temp;
    temp.word = this->word;
    if (this->iterationMode == CHANGE_LETTER)
    {
        temp.word[this->indexToChange] = this->nextLetter;
    }
    else if (this->iterationMode == INSERT_LETTER)
    {
        temp.word.insert(this->indexToChange, 1, this->nextLetter);
    }
    else if (this->iterationMode == DELETE_LETTER)
    {
        temp.word.erase(this->indexToChange,1);
    }
    else
    {
        cout << "iterationCurrent called on DONE" << endl;
    }
    return temp;
}
void Location::iterationAdvance()
{
    if (this->iterationMode == CHANGE_LETTER)
    {
        if (this->nextLetter != 'z')
        {
            this->nextLetter++;
        }
        else if (this->word.length() > this->indexToChange)
        {
            this->nextLetter = 'a';
            this->indexToChange++;
        }
        
        if (this->word.length() <= this->indexToChange)
        {
            this->iterationMode = INSERT_LETTER;
            this->nextLetter = 'a';
            this->indexToChange = 0;
        }

        if (this->word[this->indexToChange] == this->nextLetter)
        {
            this->nextLetter++;
            if (this->nextLetter == 'z')
            {
                if (this->word.length() > this->indexToChange)
                {
                    this->nextLetter = 'a';
                    this->indexToChange++;
                }
                else
                {
                    this->iterationMode = INSERT_LETTER;
                    this->nextLetter = 'a';
                    this->indexToChange = 0;
                }
            }
        }
    }
    else if (this->iterationMode == INSERT_LETTER)
    {
        if (this->nextLetter != 'z')
        {
            this->nextLetter++;
        }
        else if (this->word.length() > this->indexToChange)
        {
            this->nextLetter = 'a';
            this->indexToChange++;
        }
        else
        {
            this->iterationMode = DELETE_LETTER;
            this->indexToChange = 0;
        }
    }
    else if (this->iterationMode == DELETE_LETTER)
    {
        if (this->indexToChange < this->word.length()-1)
        {
            this->indexToChange++;
        }
        else
        {
            this->iterationMode = DONE;
        }
    }
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
    os << loc.word;
    return os;
}

istream &operator>>(istream &is, Location &loc)
{
    string temp;
    is >> temp;
    loc.word = temp;
    return is;
}

bool Location::operator<(const Location &loc) const
{
    if (this->word < loc.word)
    {
        return true;
    }
    return false;
}