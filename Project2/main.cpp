#include <iostream>
#include <map>
#include "location-proj2.h"

using namespace std;

int main()
{
    map<Location, Location> m;
    Location l;
    Location b;

    cin >> l;
    cin >> b;

    m[l] = b;

    cout << m[l] << endl;

    return 0;
}