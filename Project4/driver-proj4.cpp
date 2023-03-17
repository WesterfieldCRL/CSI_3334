#include <iostream>
#include "avl-tree-student-proj4.h"

using namespace std;

int main()
{
    AVLTree<int> tree;
    for (int i = 0; i < 10; i++) {
        tree.insert(i);
    }

    tree.printPreorder();

    tree.verifyBalance();

    cout << "DONE" << endl;

    return 0;
}