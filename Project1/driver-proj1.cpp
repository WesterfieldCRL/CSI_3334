#include "location-proj1.h"
#include "stack-proj1.h"
#include "maze-proj1.h"
#include <iostream>

using namespace std;

int main()
{
    Location loc1;
    Location loc2;
    LocationStack locStack1;

    cout << "testing with NULL top" << endl;

    cout << "printing stack" << endl;
    cout << locStack1;

    cout << "testing isOn with empty Stack" << endl;
    if (locStack1.isOn(loc1))
    {
        cout << "bad, isOn is true" << endl;
    }
    else
    {
        cout << "good, isOn is false" << endl;
    }

    cout << "testing isEmpty" << endl;
    if (locStack1.isEmpty())
    {
        cout << "good, isEmpty is true" << endl;
    }
    else
    {
        cout << "bad, isEmpty is false" << endl;
    }

    cout << endl;

    cout << "adding 5 locations to the stack" << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << "input a location" << endl;
        cin >> loc1;
        locStack1.push(loc1);
        cout << locStack1.getTop() << endl;
    }

    cout << "printing stack" << endl;
    cout << locStack1;

    cout << "testing isOn" << endl;
    if (locStack1.isOn(loc1))
    {
        cout << "good, isOn is true" << endl;
    }
    else
    {
        cout << "bad, isOn is false" << endl;
    }

    cout << "testing isEmpty" << endl;
    if (locStack1.isEmpty())
    {
        cout << "bad, isEmpty is true" << endl;
    }
    else
    {
        cout << "good, isEmpty is false" << endl;
    }

    cout << "printing stack again" << endl;
    cout << locStack1;

    cout << endl;

    cout << "testing pop" << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << locStack1.getTop() << endl;
        locStack1.pop();
    }

    cout << "printing stack" << endl;
    cout << locStack1;

    cout << "testing isOn with empty Stack" << endl;
    if (locStack1.isOn(loc1))
    {
        cout << "bad, isOn is true" << endl;
    }
    else
    {
        cout << "good, isOn is false" << endl;
    }

    cout << "testing isEmpty" << endl;
    if (locStack1.isEmpty())
    {
        cout << "good, isEmpty is true" << endl;
    }
    else
    {
        cout << "bad, isEmpty is false" << endl;
    }

    cout << "Done" << endl;

    return 0;
}

