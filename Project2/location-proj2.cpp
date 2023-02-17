/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: location-proj2.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains all the functions for the Location class.
 * The functions include the default constructor, the iterationBegin function,
 * the iterationCurrent function, the iterationAdvance function, the operator== function,
 * the operator<< function, and the operator>> function and the operator< function.
 * 
 */

#include "location-proj2.h"

/**
 * Location
 * 
 * Constructor for the Location class. 
 * Sets the word to "default", the nextLetter to 'a', 
 * the iterationMode to CHANGE_LETTER, and the indexToChange to 0.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

Location::Location() {
    this->word = "default";
    this->nextLetter = 'a';
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
}

/**
 * iterationBegin
 * 
 * Sets the nextLetter to 'a', the iterationMode to CHANGE_LETTER, 
 * and the indexToChange to 0. If the first letter of the word is 'a',
 * the nextLetter is set to 'b'.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

void Location::iterationBegin() {
    this->nextLetter = 'a';
    this->iterationMode = CHANGE_LETTER;
    this->indexToChange = 0;
    if (this->word[0] == 'a') {
        this->nextLetter++;
    }
}

/**
 * iterationCurrent
 * 
 * Returns a Location object with the word set to the current word
 * based on the iterationMode and the indexToChange. If the iterationMode
 * is CHANGE_LETTER, the word is set to the current word with the letter
 * at the indexToChange changed to the nextLetter. If the iterationMode
 * is INSERT_LETTER, the word is set to the current word with the nextLetter
 * inserted at the indexToChange. If the iterationMode is DELETE_LETTER,
 * the word is set to the current word with the letter at the indexToChange
 * deleted. The nextLetter is set to the next letter to be used in the iteration.
 * 
 * Parameters:
 *   none
 * 
 * Return value: a Location object with the word set to the modified word
 */

Location Location::iterationCurrent() const {
    Location temp;
    temp.word = this->word;
    if (this->iterationMode == CHANGE_LETTER) {
        temp.word[this->indexToChange] = this->nextLetter;
    }
    else if (this->iterationMode == INSERT_LETTER) {
        temp.word.insert(this->indexToChange, 1, this->nextLetter);
    }
    else if (this->iterationMode == DELETE_LETTER) {
        temp.word.erase(this->indexToChange,1);
    }
    return temp;
}

/**
 * iterationAdvance
 * 
 * Advances the iteration to the next word. If the iterationMode is CHANGE_LETTER,
 * the nextLetter is set to the next letter in the alphabet. If the nextLetter is 'z',
 * the indexToChange is incremented. If the indexToChange is greater than the length
 * of the word, the iterationMode is set to INSERT_LETTER, the nextLetter is set to 'a',
 * and the indexToChange is set to 0. If the nextLetter is the same as the letter at
 * the indexToChange, the nextLetter is set to the next letter in the alphabet. If the
 * nextLetter is 'z', the indexToChange is incremented. If the indexToChange is greater
 * than the length of the word, the iterationMode is set to INSERT_LETTER, the nextLetter
 * is set to 'a', and the indexToChange is set to 0. If the iterationMode is INSERT_LETTER,
 * the nextLetter is set to the next letter in the alphabet. If the nextLetter is 'z',
 * the indexToChange is incremented. If the indexToChange is greater than the length of
 * the word, the iterationMode is set to DELETE_LETTER, and the indexToChange is set to 0.
 * If the iterationMode is DELETE_LETTER, the indexToChange is incremented. If the
 * indexToChange is greater than the length of the word minus 1, the iterationMode is set
 * to DONE.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

void Location::iterationAdvance() {
    if (this->iterationMode == CHANGE_LETTER) {
        if (this->nextLetter != 'z') {
            this->nextLetter++;
        }
        else if (this->word.length() > this->indexToChange) {
            this->nextLetter = 'a';
            this->indexToChange++;
        }

        if (this->word[this->indexToChange] == this->nextLetter) {
            this->nextLetter++;
            if (this->nextLetter >= 'z') {
                this->nextLetter = 'a';
                this->indexToChange++;
            }
        }

        if (this->word.length() <= this->indexToChange) {
            this->iterationMode = INSERT_LETTER;
            this->nextLetter = 'a';
            this->indexToChange = 0;
        }
    }
    else if (this->iterationMode == INSERT_LETTER) {
        if (this->nextLetter != 'z') {
            this->nextLetter++;
        }
        else if (this->word.length() > this->indexToChange) {
            this->nextLetter = 'a';
            this->indexToChange++;
        }
        else {
            this->iterationMode = DELETE_LETTER;
            this->indexToChange = 0;
        }
    }
    else if (this->iterationMode == DELETE_LETTER) {
        if (this->indexToChange < this->word.length()-1) {
            this->indexToChange++;
        }
        else {
            this->iterationMode = DONE;
        }
    }
}

/**
 * iterationDone
 * 
 * Returns true if the iterationMode is DONE, false otherwise.
 * 
 * Parameters:
 *   none
 * 
 * Return value: tells the user if the iteration is done
 */

bool Location::iterationDone() const {
    if (this->iterationMode == DONE) {
        return true;
    }
    return false;
}

/**
 * operator==
 * 
 * Returns true if the word of the Location object passed in is the same as the word
 * of the Location object calling the function, false otherwise.
 * 
 * Parameters:
 *   loc - the Location object to compare to
 * 
 * Return value: tells the user if the words are the same
 */

bool Location::operator==(const Location &loc) const {
    if (this->word == loc.word) {
        return true;
    }
    return false;
}

/**
 * operator<<
 * 
 * Overloads the << operator to print the word of the Location object passed in.
 * 
 * Parameters:
 *   os - the ostream object to print to
 *   loc - the Location object to print
 * 
 * Return value: the ostream object to allow for input chaining
 */

ostream &operator<<(ostream &os, const Location &loc) {
    os << loc.word;
    return os;
}

/**
 * operator>>
 * 
 * Overloads the >> operator to read in a word and set the word of the Location object
 * passed in to the word read in.
 * 
 * Parameters:
 *   is - the istream object to read from
 *   loc - the Location object to set the word of
 * 
 * Return value: the istream object to allow for input chaining
 */

istream &operator>>(istream &is, Location &loc) {
    string temp;
    is >> temp;
    loc.word = temp;
    return is;
}

/**
 * operator<
 * 
 * Returns true if the word of the Location object passed in is less than the word
 * of the Location object calling the function, false otherwise.
 * 
 * Parameters:
 *   loc - the Location object to compare to
 * 
 * Return value: tells the user if the word is less than the word of the Location object
 *               passed in
 */

bool Location::operator<(const Location &loc) const {
    if (this->word < loc.word) {
        return true;
    }
    return false;
}