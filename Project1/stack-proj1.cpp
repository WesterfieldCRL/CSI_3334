#include "stack-proj1.h"
#include <iostream>


LocationStack::LocationStack()
{
    this->top = NULL;
}

LocationStack::~LocationStack()
{
    delete this->top;
}

void LocationStack::push(const Location &loc)
{
    LocationStackNode *temp = new LocationStackNode(loc,this->top);
    this->top = temp;
}

void LocationStack::pop()
{
    LocationStackNode *temp = this->top;
    this->top = top->getNextNode();
    temp->setNextNode(NULL);
    delete temp;
}

const Location &LocationStack::getTop() const
{
    return this->top->getLocation();
}

bool LocationStack::isEmpty(void) const
{
    if (this->top == NULL)
    {
        return true;
    }
    return false;
}

bool LocationStack::isOn(const Location &loc) const
{
    LocationStackNode *temp = this->top;
    while (temp != NULL)
    {
        if (temp->getLocation() == loc)
        {
            return true;
        }
        temp = temp->getNextNode();
    }
    return false;
}

ostream &operator<<(ostream &os, const LocationStack &s)
{
    LocationStackNode *temp = s.top;
    LocationStackNode *tempPrev = NULL;
    LocationStackNode *tempNext = NULL;

    //reverses links
    if (temp != NULL)
    {
        tempPrev = temp;
        temp = temp->getNextNode();
        tempPrev->setNextNode(NULL);
    }
    while (temp != NULL)
    {
        tempNext = temp->getNextNode();
        temp->setNextNode(tempPrev);
        tempPrev = temp;
        temp = tempNext;
    }
    //tempPrev now points to the top node (previously the bottom node)

    temp = tempNext = tempPrev;

    //reverses links again and prints out each location
    if (temp != NULL)
    {
        os << temp->getLocation() << endl;
        tempPrev = temp;
        temp = temp->getNextNode();
        tempPrev->setNextNode(NULL);
    }
    while (temp != NULL)
    {
        os << temp->getLocation() << endl;
        tempNext = temp->getNextNode();
        temp->setNextNode(tempPrev);
        tempPrev = temp;
        temp = tempNext;
    }

    return os;

}

LocationStackNode::LocationStackNode(const Location &loc, LocationStackNode *next)
{
    this->location = loc;
    this->nextNode = next;
}

LocationStackNode::~LocationStackNode()
{
    delete this->nextNode;
}

const Location &LocationStackNode::getLocation() const
{
    return this->location;
}

LocationStackNode *LocationStackNode::getNextNode() const
{
    return this->nextNode;
}

void LocationStackNode::setNextNode(LocationStackNode *next)
{
    this->nextNode = next;
}