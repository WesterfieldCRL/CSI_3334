#include "process-proj5.h"

/**
 * Process
 *
 * Constructor for the Process class. Initializes the id, submission time,
 * deadline, required time, and information for the process.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

Process::Process(int theId) {
    this->id = theId;
    this->submissionTime = 0;
    this->deadline = 0;
    this->requiredTime = 0;
    this->information = "";
}

/**
 * run
 *
 * This function prints the id of the process, the current system time, and
 * the information for the process. The function returns the current system
 * time plus the required time for the process.
 * 
 * Parameters:
 *   currentSystemTime - the current system time
 * 
 * Return value: the current system time plus the required time for the
 *   process
 */

int Process::run(int currentSystemTime) const {
    cout << "running process id " << this->id << " at " << currentSystemTime << endl;
    cout << this->information << endl;
    return currentSystemTime + this->requiredTime;
}

/**
 * canComplete
 *
 * This function returns true if the current system time plus the required
 * time for the process is less than or equal to the deadline for the process.
 * Otherwise, the function returns false.
 * 
 * Parameters:
 *   currentSystemTime - the current system time
 * 
 * Return value: true if the current system time plus the required time for
 *   the process is less than or equal to the deadline for the process;
 *   otherwise, false
 */

bool Process::canComplete(int currentSystemTime) const {
    if (currentSystemTime + this->requiredTime <= this->deadline) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * getId
 *
 * This function returns the id of the process.
 * 
 * Parameters:
 *   none
 * 
 * Return value: the id of the process
 */

int Process::getId() const {
    return this->id;
}

/**
 * getSubmissionTime
 *
 * This function returns the submission time of the process.
 * 
 * Parameters:
 *   none
 * 
 * Return value: the submission time of the process
 */

int Process::getSubmissionTime() const {
    return this->submissionTime;
}

/**
 * operator<
 *
 * This function returns true if the deadline for the process is less than
 * the deadline for the process p. If the deadlines are equal, the function
 * returns true if the required time for the process is less than the required
 * time for the process p. If the deadlines and required times are equal,
 * the function returns true if the id of the process is less than the id of
 * the process p. Otherwise, the function returns false.
 * 
 * Parameters:
 *   p - the process to compare to
 * 
 * Return value: true if this process is less than the process p
 *  (according to the rules above); otherwise, false
 */

bool Process::operator<(Process const &p) const {
    if (this->deadline < p.deadline) {
        return true;
    }
    else if (this->deadline > p.deadline) {
        return false;
    }
    else {
        if (this->requiredTime < p.requiredTime) {
            return true;
        }
        else if (this->requiredTime > p.requiredTime) {
            return false;
        }
        else {
            if (this->id < p.id) {
                return true;
            }
            else {
                return false;
            }
        }
    }
}

/**
 * operator>>
 *
 * This function reads the submission time, deadline, required time, and
 * information for the process from the input stream is.
 * 
 * Parameters:
 *   is - the input stream to read from
 *   p - the process to read into
 * 
 * Return value: the input stream is (for chaining)
 */

istream &operator>>(istream &is, Process &p) {
    is >> p.submissionTime >> p.deadline >> p.requiredTime;
    getline(is >> ws, p.information);
    return is;
}