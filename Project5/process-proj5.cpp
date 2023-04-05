#include "process-proj5.h"

Process::Process(int theId)
{
    this->id = theId;
    this->submissionTime = 0;
    this->deadline = 0;
    this->requiredTime = 0;
    this->information = "";
}

int Process::run(int currentSystemTime) const
{
    cout << "running process id " << this->id << " at time " << currentSystemTime << endl;
    return currentSystemTime + this->requiredTime;
}

bool Process::canComplete(int currentSystemTime) const
{
    if (currentSystemTime + this->requiredTime <= this->deadline)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Process::getId() const
{
    return this->id;
}

int Process::getSubmissionTime() const
{
    return this->submissionTime;
}

bool Process::operator<(Process const &p) const
{
    if (this->deadline < p.deadline)
    {
        return true;
    }
    else if (this->deadline > p.deadline)
    {
        return false;
    }
    else
    {
        if (this->requiredTime < p.requiredTime)
        {
            return true;
        }
        else if (this->requiredTime > p.requiredTime)
        {
            return false;
        }
        else
        {
            if (this->id < p.id)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

istream &operator>>(istream &is, Process &p)
{
    is >> p.submissionTime >> p.deadline >> p.requiredTime >> p.information;
    return is;
}