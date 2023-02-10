#include <iostream>
#include "location-proj2.h"
#include "maze-proj2.h"

using namespace std;

int main()
{
    Location test;
    Maze mazeTest;
    cin >> test;

    for (test.iterationBegin(); !test.iterationDone(); test.iterationAdvance())
    {
        cout << test.iterationCurrent() << endl;
    }

    cout << endl << "testing maze" << endl;

    cout << "input maze" << endl;
    cin >> mazeTest;

    cout << "start location = " << mazeTest.getStartLocation() << endl;

    for (int i = 0; i < 2; i++)
    {
        Location temp;
        cout << "input location" << endl;
        cin >> temp;
        if (mazeTest.isValidLocation(temp))
        {
            cout << "is valid" << endl;
        }
        else
        {
            cout << "not valid" << endl;
        }
    }

    cout << "input end location" << endl;

    cin >> test;
    if (mazeTest.isEndLocation(test))
    {
        cout << "good" << endl;
    }
    else
    {
        cout << "bad" << endl;
    }

    cout << "input non-end location" << endl;

    cin >> test;

    if (mazeTest.isEndLocation(test))
    {
        cout << "bad" << endl;
    }
    else
    {
        cout << "good" << endl;
    }

    cout << "DONE" << endl;

    return 0;
}