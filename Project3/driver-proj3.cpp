#include <iostream>
#include "bst-prof-proj3.h"
#include "bst-student-proj3.h"

using namespace std;

int main()
{
    EncryptionTree<string> tree;
    string input;

    cin >> input;

    while (input != "q")
    {
        if (input == "i")
        {
            cin >> input;
            tree.insert(input);
        }
        else if (input == "r")
        {
            cin >> input;
            tree.remove(input);
        }
        else if (input == "e")
        {
            int prev = 0;
            string word;
            getline(cin, input, '\'');
            getline(cin, input, '\'');
            cin.ignore();

            for (int i = 0; i < input.length(); i++)
            {
                if (input[i] == ' ')
                {
                    word = input.substr(prev, i-prev);
                    prev = i+1;

                    cout << tree.encrypt(word) << " ";
                }
            }
            word = input.substr(prev, input.length()-prev);
            cout << tree.encrypt(word) << endl;
        }
        else if (input == "d")
        {
            int prev = 0;
            string word;
            getline(cin, input, '\'');
            getline(cin, input, '\'');
            cin.ignore();

            for (int i = 0; i < input.length(); i++)
            {
                if (input[i] == ' ')
                {
                    word = input.substr(prev, i-prev);
                    prev = i+1;

                    cout << tree.decrypt(word) << " ";
                }
            }
            word = input.substr(prev, input.length()-prev);
            cout << tree.decrypt(word) << endl;
        }
        else if (input == "p")
        {
            tree.printPreorder();
        }
        cin >> input;
    }
    

    return 0;
}

