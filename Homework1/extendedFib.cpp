#include <iostream>

using namespace std;

int extendedFib(int n)
{
    if (n > 0 && n < 4) 
    {
        return 1;
    } 
    else if (n > 3) 
    {
        return extendedFib(n-1)+extendedFib(n-2)+extendedFib(n-3);
    } 
    else 
    {
        return extendedFib(n+3)-(extendedFib(n+1)+extendedFib(n+2));
    }
}

int main()
{
    int n;
    cin >> n;
    cout << extendedFib(n) << endl;
    return 0;
}

/*
Inputs:
4: 3
0: -1
-3: -3
9: 57
20: 46499
-20: -477
*/