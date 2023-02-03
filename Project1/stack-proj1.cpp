/* CSI 3334
 * Project 1 -- Two-dimensional Maze Solver
 * Filename: stack-proj1.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the implementation of all functions defined in stack-proj1.h
 * This file contains a constructor for locationStack class, which initalizes the top
 * pointer to NULL, a destructor which deletes the stack, the functions push and pop
 * which adds or removes nodes from the top of the stack. Also includes functions
 * for getting the top of the stack, checking if it is empty, and checking if
 * a given location is on top of the stack. This file also includes the implementation
 * of the LocationStackNode as well. It is a object that contains a pointer to the
 * next node and a Location. It has a constructor, a destructor, a way to get the
 * Location, a way to set the location, and a way to set the pointer to a Node.
 */

#include "stack-proj1.h"
#include <iostream>

/**
 * LocationStack
 * 
 * Constructor for the LocationStack class.
 * Sets top to Null
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */
LocationStack::LocationStack() {
    this->top = NULL;
}

/**
 * ~LocationStack
 * 
 * Destructor for the LocationStack class.
 * delete's top
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */
LocationStack::~LocationStack() {
    delete this->top;
}

/**
 * push
 * 
 * Constructor for the LocationStack class.
 * creates a temporary node using loc
 * and sets top to its next.
 * then sets top to be the temporary node.
 * 
 * Parameters:
 *   loc: Location object, object that is being pushed on the top of the stack.
 * 
 * Return value: none
 */
void LocationStack::push(const Location &loc) {
    LocationStackNode *temp = new LocationStackNode(loc,this->top);
    this->top = temp;
}

/**
 * pop
 * 
 * removes the top of the stack
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */
void LocationStack::pop() {
    LocationStackNode *temp = this->top;
    this->top = top->getNextNode();
    temp->setNextNode(NULL);
    delete temp;
}

/**
 * getTop
 * 
 * returns the top Location on the stack
 * 
 * Parameters:
 *   none
 * 
 * Return value: The Location object on the top of the stack
 */
const Location &LocationStack::getTop() const {
    return this->top->getLocation();
}

/**
 * isEmpty
 * 
 * Checks to see if there are any nodes on the stack
 * and if there are none returns true, otherwise false.
 * 
 * Parameters:
 *   none
 * 
 * Return value: A boolean to tell the user if the stack is empty or not
 */
bool LocationStack::isEmpty() const {
    if (this->top == NULL) {
        return true;
    }
    return false;
}

/**
 * isOn
 * 
 * takes the provided Location and checks to see if it is equal
 * to the location on the top of the stack.
 * 
 * Parameters:
 *   loc: Location object, object being checked to see if an equivalent Location
 *      is on the stack
 * 
 * Return value: A boolean to tell the user if the provided Location is on the stack
 */
bool LocationStack::isOn(const Location &loc) const {
    LocationStackNode *temp = this->top;
    while (temp != NULL) {
        if (temp->getLocation() == loc) {
            return true;
        }
        temp = temp->getNextNode();
    }
    return false;
}

/**
 * operator<<
 * 
 * outputs the contents of the provided stack to the provided ostream
 * 
 * Parameters:
 *   os: ostream. to output the stack to
 *   s: LocationStack, the thing to be outputted
 * 
 * Return value: the given ostream to permit output chaining
 */
ostream &operator<<(ostream &os, const LocationStack &s) {
    LocationStackNode *temp = s.top;
    LocationStackNode *tempPrev = NULL;
    LocationStackNode *tempNext = NULL;

    //reverses links
    if (temp != NULL) {
        tempPrev = temp;
        temp = temp->getNextNode();
        tempPrev->setNextNode(NULL);
    }
    while (temp != NULL) {
        tempNext = temp->getNextNode();
        temp->setNextNode(tempPrev);
        tempPrev = temp;
        temp = tempNext;
    }
    //tempPrev now points to the top node (previously the bottom node)

    temp = tempNext = tempPrev;

    //reverses links again and prints out each location
    if (temp != NULL) {
        os << temp->getLocation() << endl;
        tempPrev = temp;
        temp = temp->getNextNode();
        tempPrev->setNextNode(NULL);
    }
    while (temp != NULL) {
        os << temp->getLocation() << endl;
        tempNext = temp->getNextNode();
        temp->setNextNode(tempPrev);
        tempPrev = temp;
        temp = tempNext;
    }

    return os;

}

/**
 * LocationStackNode
 * 
 * Constructor for a
 * Node with a pointer to a next node, and a Location value
 * The next Node has a default value of NULL
 * 
 * Parameters:
 *   loc: object that nextNode will point to
 *   next: LocationStackNode, next node in the link, default is NULL
 * 
 * Return value: none
 */
LocationStackNode::LocationStackNode(const Location &loc, LocationStackNode *next) {
    this->location = loc;
    this->nextNode = next;
}

/**
 * ~LocationStackNode
 * 
 * Destructor for the LocationStackNode
 * delete's the pointer to the next node,
 * which will call that nodes destructor as well 
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */
LocationStackNode::~LocationStackNode() {
    delete this->nextNode;
}

/**
 * getLocation
 * 
 * returns the location stored by the node
 * 
 * Parameters:
 *   none
 * 
 * Return value: the object stored in this Node
 */
const Location &LocationStackNode::getLocation() const {
    return this->location;
}

/**
 * getNextNode
 * 
 * returns the node this node is pointing too
 * 
 * Parameters:
 *   none
 * 
 * Return value: The node pointed to by this node
 */
LocationStackNode *LocationStackNode::getNextNode() const {
    return this->nextNode;
}

/**
 * setNextNode
 * 
 * sets the pointer to the provided node
 * 
 * Parameters:
 *   next: LocationStackNode, the node to point this node too
 * 
 * Return value: none
 */
void LocationStackNode::setNextNode(LocationStackNode *next) {
    this->nextNode = next;
}