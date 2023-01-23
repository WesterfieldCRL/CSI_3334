/* CSI 3334
 * Project 0 -- Undo Redo
 * Filename: driver-proj0.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the main function for this program.
 * The main function includes the libraries:
 * iostream,string,stack,cassert
 * uses namespace std
 * The main contains the implementation of a simplified text editor.
 * It gets inputs from the user and based on those inputs performs either an undo
 * operation, a redo operation, or adds text to the output. 
 * It will output the result of the input after doing all the undos and redos.
 * Further details are available in the function documentation
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
 *  This function takes input from the user and keeps track of the input provided
 * The user must input an integer at the start of the program to determine
 * the number of times they will provide input.The user will then
 * input either u, r, or t followed by a string. u tells the program to undo the last
 * text input. The last text input will be removed from the text stack and added to the top
 * of the undo stack. r tells the program to redo the undo, and the text from the top
 * of the undo stack will be removed and added to the top of the text stack. For either,
 * if there is nothing to undo/redo and error message will be printed. t " " tells the 
 * program to add the provided string to the text stack. After all input has been gathered,
 * the program will print two lines: the contents of the text stack and the contents of the
 * undo stack.
 */
int main(int argc, char **argv) {
    //argc and argv allow the user to pass additional 
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
