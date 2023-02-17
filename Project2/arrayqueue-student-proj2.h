/* CSI 3334
 * Project 2 -- Word Melt Shortest-Path Solver
 * Filename: arrayqueue-student-proj2.h
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains all the functions for the ArrayQueue class.
 * The ArrayQueue class is a queue that uses a circular array to store the data.
 * The ArrayQueue class has a constructor that sets the capacity to 10, length to 0,
 * front to 0, and data to a new array of size 10. The copy constructor creates a new
 * array of the same size as the array in the parameter and copies the data from the
 * parameter array to the new array. The destructor deletes the array. The add function
 * adds an item to the back of the queue. If the queue is full, the capacity is doubled.
 * The remove function removes an item from the front of the queue. The getFront function
 * returns the item at the front of the queue. The getLength function returns the length
 * of the queue. The assignment operator creates a new array of the same size as the
 * array in the parameter and copies the data from the parameter array to the new array.
 * The doubleCapacity function doubles the capacity of the queue by creating a new array
 * of twice the size of the current array and copying the data from the current array to
 * the new array making sure to wrap around the array if the front is not at the beginning
 * of the array.
 */

#ifndef ARRAY_QUEUE_STUDENT_PROJ2_H
#define ARRAY_QUEUE_STUDENT_PROJ2_H

#include "arrayqueue-prof-proj2.h"
#include <cassert>

/**
 * ArrayQueue
 * 
 * Constructor for the ArrayQueue class.
 * Sets the capacity to 10, length to 0, front to 0, 
 * and data to a new array of size 10.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <class Base>
ArrayQueue<Base>::ArrayQueue() {
    this->capacity = 10;
    this->length = 0;
    this->front = 0;
    this->data = new Base[this->capacity];
}

/**
 * ArrayQueue
 * 
 * Copy constructor for the ArrayQueue class.
 * Creates a new array of the same size as the array in the parameter
 * and copies the data from the parameter array to the new array.
 * 
 * Parameters:
 *   q: the queue to be copied
 * 
 * Return value: none
 */

template <class Base>
ArrayQueue<Base>::ArrayQueue(const ArrayQueue<Base> &q) {
    this->data = new Base[q.capacity];
    this->length = q.length;
    this->capacity = q.capacity;

    for (int i = 0; i < q.capacity; i++)
    {
        this->data[i] = q.data[i];
    }
}

/**
 * ~ArrayQueue
 * 
 * Deletes the array.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <class Base>
ArrayQueue<Base>::~ArrayQueue() {
    delete [] this->data;
}

/**
 * add
 * 
 * Adds an item to the back of the queue by using
 * the length and capacity to determine where to add the item
 * in the circular array.
 * If the queue is full, doubleCapacity is called.
 * 
 * Parameters:
 *   item: the item to be added to the queue
 * 
 * Return value: none
 */

template <class Base>
void ArrayQueue<Base>::add(const Base &item) {
    if (this->length >= this->capacity)
    {
        doubleCapacity();
    }
    int back = (this->front+this->length) % this->capacity;
    this->data[back] = item;
    this->length++;
}

/**
 * remove
 * 
 * Removes an item from the front of the queue by
 * incrementing the front using capacity to wrap around the array
 * and decrementing the length.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <class Base>
void ArrayQueue<Base>::remove() {
    this->front = (this->front+1)%this->capacity;
    this->length--;
}

/**
 * getFront
 * 
 * Returns the item at the front of the queue.
 * 
 * Parameters:
 *   none
 * 
 * Return value: the item at the front of the queue
 */

template <class Base>
const Base &ArrayQueue<Base>::getFront() const {
    return this->data[this->front];
}

/**
 * getLength
 * 
 * Returns the length of the queue.
 * 
 * Parameters:
 *   none
 * 
 * Return value: the length of the queue
 */

template <class Base>
int ArrayQueue<Base>::getLength() const {
    return this->length;
}

/**
 * operator=
 * 
 * Creates a new array of the same size as the array in the parameter
 * and copies the data from the parameter array to the new array.
 * 
 * Parameters:
 *   q: the queue to be copied
 * 
 * Return value: the new queue
 */

template <class Base>
const ArrayQueue<Base> &ArrayQueue<Base>::operator=(const ArrayQueue<Base> &q) {
    if (this != &q) {
        delete [] this->data;
        this->capacity = q.capacity;
        this->length = q.length;
        this->front = q.front;

        this->data = new Base[this->capacity];

        for (int i = 0; i < this->capacity; i++) {
            this->data[i] = q.data[i];
        }
    }
    return *this;
}

/**
 * doubleCapacity
 * 
 * Doubles the capacity of the queue by creating a new array
 * of twice the size of the current array and copying the data
 * from the current array to the new array making sure to wrap
 * around the array if the front is not at the beginning of the array.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <class Base>
void ArrayQueue<Base>::doubleCapacity() {
    this->capacity *= 2;
    Base *temp = this->data;
    this->data = new Base[this->capacity];
    int back = -1;

    for (int i = 0; i < this->length; i++) {
        back++;
        this->data[back] = temp[front];
        this->front = (front+1)%this->length;
    }
    delete [] temp;
}


#endif