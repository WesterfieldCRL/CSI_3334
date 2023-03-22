#include <iostream>
#include "avl-tree-student-proj4.h"

using namespace std;

int main()
{
    EncryptionTree<string> tree;
    string input;
    const string *decryptWord;

    cin >> input;

    while (input != "q") {
        if (input == "i") {
            cin >> input;
            tree.insert(input);
        }
        else if (input == "r") {
            cin >> input;
            tree.remove(input);
        }
        else if (input == "e") {
            int prev = 0;
            string word;
            getline(cin, input, '\'');
            getline(cin, input, '\'');
            cin.ignore();
            int length = input.length();
            for (int i = 0; i < length; i++) {
                if (input[i] == ' ') {
                    word = input.substr(prev, i-prev);
                    prev = i+1;

                    cout << tree.encrypt(word) << " ";
                }
            }
            word = input.substr(prev, input.length()-prev);
            cout << tree.encrypt(word) << endl;
        }
        else if (input == "d") {
            int prev = 0;
            string word;
            getline(cin, input, '\'');
            getline(cin, input, '\'');
            cin.ignore();
            int length = input.length();
            for (int i = 0; i < length; i++) {
                if (input[i] == ' ') {
                    word = input.substr(prev, i-prev);
                    prev = i+1;
                    decryptWord = tree.decrypt(word);
                    if (decryptWord != NULL) {
                        cout << *decryptWord << " ";
                    }
                    else {
                        cout << "? ";
                    }
                }
            }
            word = input.substr(prev, input.length()-prev);
            decryptWord = tree.decrypt(word);
            if (decryptWord != NULL) {
                cout << *decryptWord << endl;
            }
            else {
                cout << "?" << endl;
            }
        }
        else if (input == "p") {
            tree.printPreorder();
        }
        else if (input == "l")
        {
            tree.printLevelOrder();
        }
        cin >> input;
    }

    return 0;
}