#include <iostream>
#include "bst-prof-proj3.h"
#include "bst-student-proj3.h"

using namespace std;

int main()
{
    BSTNode<int> left(1);
    BSTNode<int> right(2);
    BSTNode<int> root(3, &left, &right);

    root.printPreorder(cout,"");

    cout << root.getData() << endl;

    cout << root.minNode()->getData() << endl;
    cout << root.maxNode()->getData() << endl;

    return 0;
}