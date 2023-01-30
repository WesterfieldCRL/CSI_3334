#include "location-proj1.h"
#include "stack-proj1.h"
#include "maze-proj1.h"
#include <iostream>

using namespace std;

int main()
{
    Maze maze;
    Location m;
    Location neighbor;
    LocationStack stack;
    bool NoSolution = false;

    cin >> maze;

    m = maze.getStartLocation();
    stack.push(m);

    while (!NoSolution && !maze.isEndLocation(stack.getTop()))
    {
        m = stack.getTop();
        stack.pop();
        if (!m.iterationDone())
        {
            neighbor = m.iterationCurrent();
            neighbor.iterationBegin();
            m.iterationAdvance();
            stack.push(m);
            if (!stack.isOn(neighbor) && maze.isValidLocation(neighbor))
            {
                stack.push(neighbor);
            }
            //cout << stack << endl << endl;
            //cout << "n = " << neighbor << endl;
        }
        else if (stack.isEmpty())
        {
            NoSolution = true;
        }
    }

    if (!NoSolution)
    {
        cout << "Solution found" << endl;
        cout << stack;
    }
    else
    {
        cout << "No solution" << endl;
    }


    return 0;
}

