#include <iostream>
#include <random>
#include "arrayheap-student-proj6.h"


using namespace std;

int main()
{
    ArrayHeap<int> testHeap;
    srand(time(0));

    for (int i = 0; i < 50; i++)
    {
        int IorR = rand()%2;
        if (IorR == 0)
        {
            int temp = rand()%100;
            testHeap.insert(temp);
            cout << "inserting " << temp << endl;
        }
        else
        {
            if (testHeap.getNumItems() > 0)
            {
                cout << "removing " << testHeap.getMinItem() << endl;
                testHeap.removeMinItem();
            }
            else
            {
                cout << "no items in heap" << endl;
            }
        }
    }

    cout << endl;
    cout << testHeap.getNumItems() << endl;

    

    return 0;
}