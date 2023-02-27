#include <iostream>
#include <random>
#include <string>
#include "bst-prof-proj3.h"
#include "bst-student-proj3.h"

using namespace std;

int main()
{

    BST<string> tree;
    int lines;

    mt19937 generator{random_device{}()};
    //modify range according to your need "A-Z","a-z" or "0-9" or whatever you need.
    uniform_int_distribution<int> distribution{'a', 'z'};

    srand(time(0));

    lines = rand() % 100;

    for (int i = 0; i < lines; i++)
    {
        int generate_len = rand()%5 + 2;
        string rand_str(generate_len, '\0');
        for(auto& dis: rand_str)
            dis = distribution(generator);
        tree.insert(rand_str);
    }

    tree.verifySearchOrder();

    /*EncryptionTree<string> tree;
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
    }*/
    

    return 0;
}

