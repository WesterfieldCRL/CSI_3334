/* CSI 3334
 * Project 6 -- Network Brodcasting
 * Filename: arrayheap-student-proj6.h
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the implementation of the ArrayHeap class.
 */

#ifndef ARRAY_HEAP_STUDENT_PROJ6_H
#define ARRAY_HEAP_STUDENT_PROJ6_H

#include "arrayheap-prof-proj6.h"
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * ArrayHeap
 *
 * This function is the constructor for the ArrayHeap class. It initializes the
 * heap and free stack arrays to the correct size.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <typename T>
ArrayHeap<T>::ArrayHeap() {
    this->capacity = 10;
    this->numItems = 0;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];
    this->dataToHeap = new int[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        this->heapAndFreeStack[i] = -1;
        this->dataToHeap[i] = -1;
    }
}

/**
 * ArrayHeap
 *
 * This function is the copy constructor for the ArrayHeap class. It copies
 * the heap and free stack arrays from the given ArrayHeap.
 * 
 * Parameters:
 *   h - the ArrayHeap to copy
 * 
 * Return value: none
 */

template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h) {
    this->capacity = h.capacity;
    this->numItems = h.numItems;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];
    this->dataToHeap = new int[this->capacity];

    for(int i = 0; i < this->capacity; i++) {
        this->data[i] = h.data[i];
        this->heapAndFreeStack[i] = h.heapAndFreeStack[i];
        this->dataToHeap[i] = h.dataToHeap[i];
    }
}

/**
 * ~ArrayHeap
 *
 * This function is the destructor for the ArrayHeap class. It frees the memory
 * allocated for the heap and free stack arrays.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <typename T>
ArrayHeap<T>::~ArrayHeap() {
    delete [] this->data;
    delete [] this->heapAndFreeStack;
    delete [] this->dataToHeap;
    this->capacity = 0;
    this->numItems = 0;
}

/**
 * operator=
 *
 * This function is the assignment operator for the ArrayHeap class. It copies
 * the heap and free stack arrays from the given ArrayHeap.
 * 
 * Parameters:
 *   ah - the ArrayHeap to copy
 * 
 * Return value: a reference to the ArrayHeap
 */

template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah) {
    this->capacity = ah.capacity;
    this->numItems = ah.numItems;
    delete [] this->data;
    delete [] this->heapAndFreeStack;
    delete [] this->dataToHeap;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];
    this->dataToHeap = new int[this->capacity];

    for(int i = 0; i < this->capacity; i++) {
        this->data[i] = ah.data[i];
        this->heapAndFreeStack[i] = ah.heapAndFreeStack[i];
        this->dataToHeap[i] = ah.dataToHeap[i];
    }

    return *this;
}

/**
 * doubleCapacity
 *
 * This function doubles the capacity of the heap and free stack arrays.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <typename T>
int ArrayHeap<T>::insert(T const &item) {
    if(this->numItems >= this->capacity) {
        this->doubleCapacity();
    }

    for (int i = 0; i < this->capacity; i++) {
        if (this->dataToHeap[i] == -1) {
            this->data[i] = item;
            this->heapAndFreeStack[this->numItems] = i;
            this->dataToHeap[i] = this->numItems;
            i = this->capacity + 1;
        }
    }

    this->bubbleUp(this->numItems);
    this->numItems++;

    return this->numItems - 1;
}

/**
 * removeMinItem
 *
 * This function removes the minimum item from the heap.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */
 
template <typename T>
void ArrayHeap<T>::removeMinItem() {
    if(this->numItems <= 0) {
        return;
    }

    this->dataToHeap[this->heapAndFreeStack[this->numItems - 1]] = 0;
    this->dataToHeap[this->heapAndFreeStack[0]] = -1;
    
    this->heapAndFreeStack[0] = this->heapAndFreeStack[this->numItems - 1];
    this->numItems--;
    this->bubbleDown(0);
}

/**
 * getMinItem
 *
 * This function returns the minimum item from the heap.
 * 
 * Parameters:
 *   none
 * 
 * Return value: the minimum item
 */

template <typename T>
T const &ArrayHeap<T>::getMinItem() const {
    return this->data[this->heapAndFreeStack[0]];
}

/**
 * getNumItems
 *
 * This function returns the number of items in the heap.
 * 
 * Parameters:
 *   none
 * 
 * Return value: the number of items in the heap
 */

template <typename T>
int ArrayHeap<T>::getNumItems() const {
    return this->numItems;
}

/**
 * isOnHeap
 *
 * This function returns whether or not the given key is on the heap.
 * 
 * Parameters:
 *   key - the key to check
 * 
 * Return value: whether or not the given key is on the heap
 */

template <typename T>
bool ArrayHeap<T>::isOnHeap(int key) const {
    bool isOnHeap = false;
    if (0 <= key && key < this->capacity) {
        if (0 <= this->dataToHeap[key] && this->dataToHeap[key] < this->numItems) {
            if (this->heapAndFreeStack[this->dataToHeap[key]] == key) {
                isOnHeap = true;
            }
        }
    }
    return isOnHeap;
}

/**
 * changeItemAtKey
 *
 * This function changes the item at the given key to the given item.
 * 
 * Parameters:
 *   key - the key to check
 *   newItem - the item to change to
 * 
 * Return value: none
 */

template <typename T>
void ArrayHeap<T>::changeItemAtKey(int key, T const &newItem) {
    if(this->dataToHeap[key] == -1) {
        return;
    }

    this->data[this->heapAndFreeStack[key]] = newItem;
    this->bubbleUp(this->heapAndFreeStack[key]);
    this->bubbleDown(this->heapAndFreeStack[key]);
}

/**
 * doubleCapacity
 *
 * This function doubles the capacity of the heap and free stack arrays.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <typename T>
void ArrayHeap<T>::doubleCapacity() {
    this->capacity *= 2;
    T *newData = new T[this->capacity];
    int *newHeapAndFreeStack = new int[this->capacity];
    int *newDataToHeap = new int[this->capacity];

    for (int i = 0; i < this->capacity; i++) {
        newDataToHeap[i] = -1;
    }

    for(int i = 0; i < this->numItems; i++) {
        newData[i] = this->data[i];
        newHeapAndFreeStack[i] = this->heapAndFreeStack[i];
        newDataToHeap[i] = this->dataToHeap[i];
    }

    delete [] this->data;
    delete [] this->heapAndFreeStack;
    delete [] this->dataToHeap;
    this->data = newData;
    this->heapAndFreeStack = newHeapAndFreeStack;
    this->dataToHeap = newDataToHeap;
}

/**
 * bubbleUp
 *
 * This function bubbles up the item at the given index.
 * 
 * Parameters:
 *   ndx - the index to bubble up
 * 
 * Return value: none
 */

template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx) {
    int parent = (ndx - 1) / 2;
    if(parent < 0) {
        return;
    }

    if(this->data[this->heapAndFreeStack[ndx]] < this->data[this->heapAndFreeStack[parent]]) {
        swap(this->heapAndFreeStack[ndx], this->heapAndFreeStack[parent]);
        swap(this->dataToHeap[this->heapAndFreeStack[ndx]], this->dataToHeap[this->heapAndFreeStack[parent]]);
        this->bubbleUp(parent);
    }
}

/**
 * bubbleDown
 *
 * This function bubbles down the item at the given index.
 * 
 * Parameters:
 *   ndx - the index to bubble down
 * 
 * Return value: none
 */

template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx) {
    int leftChild = (2 * ndx) + 1;
    int rightChild = (2 * ndx) + 2;
    int minChild = leftChild;

    if(leftChild >= this->numItems) {
        return;
    }

    if(rightChild < this->numItems && this->data[this->heapAndFreeStack[rightChild]] < this->data[this->heapAndFreeStack[leftChild]]) {
        minChild = rightChild;
    }

    if(this->data[this->heapAndFreeStack[minChild]] < this->data[this->heapAndFreeStack[ndx]]) {
        swap(this->heapAndFreeStack[ndx], this->heapAndFreeStack[minChild]);
        swap(this->dataToHeap[this->heapAndFreeStack[ndx]], this->dataToHeap[this->heapAndFreeStack[minChild]]);
        this->bubbleDown(minChild);
    }
}

#endif

