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
    while (cin >> input && input != "NEXT") {
        tree.insert(input);
    }

    tree.printPreorder();

    tree.verifyBalance();
    tree.verifySearchOrder();

    while (cin >> input && input != "DONE") {
        tree.remove(input);
        tree.printPreorder();

        tree.verifyBalance();
        tree.verifySearchOrder();
    }

    tree.printPreorder();

    tree.verifyBalance();
    tree.verifySearchOrder();

    cout << "DONE" << endl;

    return 0;
}