#include <iostream>
#include "avl-tree-student-proj4.h"

using namespace std;

int main()
{
    AVLTree<string> tree;
    /*for (int i = 0; i < 10; i++) {
        tree.insert(i);
    }*/
    string input;
    while (cin >> input && input != "DONE") {
        tree.insert(input);
    }

    tree.printPreorder();

    tree.verifyBalance();

    cout << "DONE" << endl;

    return 0;
}