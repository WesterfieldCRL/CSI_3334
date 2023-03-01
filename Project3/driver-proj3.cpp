/* CSI 3334
 * Project 3 -- Tree-Based Encryption
 * Filename: driver-proj3.cpp
 * Student name: Wesley Anastasi
 * version: 1.7
 * 
 * This file contains the main function for this program.
 * The main function includes iostream, string, bst-prof-proj3.h, bst-student-proj3.h
 * and uses namespace std. The main function contains the implementation of a simple
 * encryption program that uses a binary search tree to encrypt and decrypt words.
 * The program will take several different commands from the user. The commands are
 * i, r, e, d, and q. The i command will insert a word into the tree. The r command
 * will remove a word from the tree. The e command will encrypt a word. The d command
 * will decrypt a word. The q command will quit the program. The program will continue
 * to take commands until the q command is entered.
 */

#include <iostream>
#include <string>
#include "bst-prof-proj3.h"
#include "bst-student-proj3.h"

using namespace std;

/**
 * main
 *
 * This function uses the functions provided by the EncryptionTree class,
 * to implement a simple encryption program. When the
 * program is run, the user will be prompted to enter a command. For
 * each command, the program will perform the appropriate action. 
 * When given the i command, the program will insert a word into the tree by
 * calling the insert function. When given the r command, the program will remove
 * a word from the tree by calling the remove function. When given the e command,
 * the program will encrypt a word and print the encrypted word to the screen.
 * Getline is used to get the path to be encrypted. The program then
 * uses substr to get each word in the path and calls the encrypt function
 * to encrypt each word. The program then prints the encrypted word to the screen.
 * When given the d command, the program will decrypt a word. The uses the same
 * method as encrypt to get each word in the path. The program then calls the
 * decrypt function to decrypt each word. If the word is not in the tree, the
 * program will print a ? to the screen. The program then prints the decrypted
 * path to the screen. When given the p command, the program will print the tree
 * in preorder by calling the printPreorder function. When given the q command,
 * the program will quit.
 * 
 * Parameters:
 *   none
 * 
 * Return value: 0 (indicating a successful run)
 */

int main() {

    EncryptionTree<string> tree;
    string input;
    const string *decryptWord = new string;

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

            for (int i = 0; i < input.length(); i++) {
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
        cin >> input;
    }
    

    return 0;
}

