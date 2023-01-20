/* CSI 3334
 * Project 0 -- Undo Redo
 * Filename: driver-proj0.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the main for project 0
 * Project 0 is a simple text editor with undo and redo functions
 */
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <sstream>

using namespace std;

/* main
 *  parameters:
 *      argc -- the number of arguments from the command line
 *      argv -- the command line argument values
 *  return value: 0 (indicating a successful run)
 * 
 *  Takes an integer input and gets input that many times, user inputs
 * u for undo, r for redo, and t for normal text
 * at the end of the program, will output the text and undo stacks
 */
int main(int argc, char **argv) {
    //argc and argv allow the user to pass additonal 
    //arguments into the function from the command line 
    const string undoChar = "u";
    const string redoChar = "r";
    const string textChar = "t";
    // these are the two stacks used to store the typed words and the undone
    // words
    stack<string> typing, undo;
    int length;
    string input;
    int textStackSize = 0;
    int undoStackSize = 0;

    cin >> length;

    for (int i = 0; i < length; i++) {
        cin >> input;

        if (input == undoChar) {
            if (typing.empty()) {
                cout << "nothing to undo on command " << i+1 << endl;
            }
            else {
                undo.push(typing.top());
                typing.pop();
            }
        }
        else if (input == redoChar) {
            if (undo.empty()) {
                cout << "nothing to redo on command " << i+1 << endl;
            }
            else {
                typing.push(undo.top());
                undo.pop();
            }
        }
        else if (input == textChar) {
            cin >> input;
            typing.push(input);
        }
    }

    //output typing stack
    while (!typing.empty()) {
        textStackSize++;
        undo.push(typing.top());
        typing.pop();
    }

    for (int i = 0; i < textStackSize; i++) {
        cout << undo.top();
        if (i < textStackSize-1) {
            cout << " ";
        }
        undo.pop();
    }

    cout << endl;

    //output undo stack
    while (!undo.empty()) {
        undoStackSize++;
        typing.push(undo.top());
        undo.pop();
    }

    for (int i = 0; i < undoStackSize; i++) {
        cout << typing.top();
        if (i < undoStackSize-1) {
            cout << " ";
        }
        typing.pop();
    }

    cout << endl;

    return 0;
}
