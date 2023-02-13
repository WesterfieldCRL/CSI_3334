#include <iostream>
#include "location-proj2.h"
#include "maze-proj2.h"
#include "arrayqueue-prof-proj2.h"
#include "arrayqueue-student-proj2.h"

using namespace std;

int main()
{
    ArrayQueue<int> q;
    ArrayQueue<int> p;

    for (int i = 0; i < 20; i++)
    {
        q.add(i);
    }

    p = q;

    for (int i = 0; i < 20; i++)
    {
        cout << q.getFront() << " " << q.getLength() << endl;
        q.remove();
    }

    cout << "p front = " << p.getFront() << endl;

    cout << "DONE" << endl;

    return 0;
}