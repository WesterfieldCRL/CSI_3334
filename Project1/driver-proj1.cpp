#include "location-proj1.h"
#include <iostream>

using namespace std;

int main()
{
    Location loc;
    Location loc2;

    for (loc.iterationBegin(); !loc.iterationDone(); loc.iterationAdvance()) {
        Location neighbor = loc.iterationCurrent();
        cout << neighbor << endl;
    }

    //set to different location
    cin >> loc2;

    if (loc == loc2)
    {
        cout << "bad" << endl;
    }
    else
    {
        cout << "not equal" << endl;
    }

    for (loc2.iterationBegin(); !loc2.iterationDone(); loc2.iterationAdvance()) {
        Location neighbor = loc2.iterationCurrent();
        cout << neighbor << endl;
    }

    //set back to same location
    cin >> loc2;

    if (loc == loc2)
    {
        cout << "equal!" << endl;
    }

    return 0;
}

