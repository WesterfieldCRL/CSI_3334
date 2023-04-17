/* CSI 3334
 * Project 5 -- Real-Time Batch Operating System Simulator
 * Filename: arrayheap-student-proj5.h
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the ArrayHeap class. The ArrayHeap class is a heap
 * implemented using an array. The heap is implemented using a min-heap.
 * The heapAndFreeStack array is used to keep track of the free spaces in the
 * data array. The heapAndFreeStack array is implemented using a max-heap.
 * This file implements the constructor, copy constructor, destructor, and
 * assignment operator, insert, removeMinItem, getMinItem, bubbleUp,
 * bubbleDown, and doubleCapacity functions.
 */

#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>

using namespace std;

/**
 * ArrayHeap
 *
 * Constructor for the ArrayHeap class. Initializes the capacity, number of
 * items, and the data and heapAndFreeStack arrays.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <typename T>
ArrayHeap<T>::ArrayHeap() {
    this->capacity = 1;
    this->numItems = 0;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];
}

/**
 * ArrayHeap
 *
 * Copy constructor for the ArrayHeap class. Initializes the capacity, number
 * of items, and the data and heapAndFreeStack arrays. Copies the data from
 * the parameter into the new heap.
 * 
 * Parameters:
 *   h - the heap to copy
 * 
 * Return value: none
 */

template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h) {
    this->capacity = h.capacity;
    this->numItems = h.numItems;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];
    for(int i = 0; i < this->capacity; i++) {
        this->data[i] = h.data[i];
        this->heapAndFreeStack[i] = h.heapAndFreeStack[i];
    }
}

/**
 * ~ArrayHeap
 *
 * Destructor for the ArrayHeap class. Frees the memory allocated for the
 * data and heapAndFreeStack arrays.
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
    this->capacity = 0;
    this->numItems = 0;
}

/**
 * operator=
 *
 * Assignment operator for the ArrayHeap class. Frees the memory allocated
 * for the data and heapAndFreeStack arrays. Initializes the capacity, number
 * of items, and the data and heapAndFreeStack arrays. Copies the data from
 * the parameter into the new heap.
 * 
 * Parameters:
 *   h - the heap to copy
 * 
 * Return value: a reference to the current heap
 */

template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah) {
    if(this != &ah) {
        this->capacity = ah.capacity;
        this->numItems = ah.numItems;
        this->data = new T[this->capacity];
        this->heapAndFreeStack = new int[this->capacity];
        for(int i = 0; i < this->capacity; i++) {
            this->data[i] = ah.data[i];
            this->heapAndFreeStack[i] = ah.heapAndFreeStack[i];
        }
    }
    return *this;
}

/**
 * insert
 *
 * Inserts an item into the heap. If the heap is full, the capacity is
 * doubled. The item is inserted into the first free slot in the heap. The
 * heapAndFreeStack array is updated to reflect the new item. The bubbleUp
 * function is called to restore the heap property.
 * 
 * Parameters:
 *   item - the item to insert
 * 
 * Return value: none
 */

template <typename T>
void ArrayHeap<T>::insert(T const &item) {

    if(this->numItems == this->capacity) {
        this->doubleCapacity();
    }

    this->data[this->numItems] = item;
    this->heapAndFreeStack[this->numItems] = this->numItems;
    this->numItems++;


    this->bubbleUp(this->numItems - 1);
}

/**
 * removeMinItem
 *
 * Removes the minimum item from the heap. Copies the last item in the heap
 * to the first position in the heap, decrements the number of items in the
 * heap, and calls the bubbleDown function to restore the heap property.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <typename T>
void ArrayHeap<T>::removeMinItem() {

    //this->data[this->heapAndFreeStack[0]] = this->data[this->heapAndFreeStack[this->numItems-1]];
    data[0] = data[numItems-1];
    this->numItems--;
    this->bubbleDown(0);
}

/**
 * getMinItem
 *
 * Returns the minimum item in the heap.
 * 
 * Parameters:
 *   none
 * 
 * Return value: the minimum item in the heap
 */

template <typename T>
T const &ArrayHeap<T>::getMinItem() const {
    //return this->data[this->heapAndFreeStack[0]];
    return data[0];
}

/**
 * getNumItems
 *
 * Returns the number of items in the heap.
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
 * bubbleUp
 *
 * Restores the heap property by swapping the item at the specified index
 * with its parent if the parent is larger. The function is called
 * recursively until the heap property is restored.
 * 
 * Parameters:
 *   ndx - the index of the item to bubble up
 * 
 * Return value: none
 */

template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx) {
    if (ndx == 0) {
        return;
    }
    /*int parent = (ndx - 1) / 2;
    if (this->data[this->heapAndFreeStack[ndx]] < this->data[this->heapAndFreeStack[parent]]) {
        swap(this->heapAndFreeStack[ndx], this->heapAndFreeStack[parent]);
        this->bubbleUp(parent);
    }*/
    int parent = (ndx - 1) / 2;
    if (this->data[ndx] < this->data[parent])
    {
        swap(this->data[ndx], this->data[parent]);
        swap(this->heapAndFreeStack[ndx], this->heapAndFreeStack[parent]);
        this->bubbleUp(parent);
    }
}

/**
 * bubbleDown
 *
 * Restores the heap property by swapping the item at the specified index
 * with its smaller child if the child is smaller. The function is called
 * recursively until the heap property is restored.
 * 
 * Parameters:
 *   ndx - the index of the item to bubble down
 * 
 * Return value: none
 */

template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx) {
    /*int child1 = (ndx * 2) + 1;
    int child2 = (ndx * 2) + 2;
    if (child1 < this->numItems) {
        int lesserChild = child1;
        if ((child2 < this->numItems) && (this->data[this->heapAndFreeStack[child2]] < 
        this->data[this->heapAndFreeStack[child1]])) {
            lesserChild = child2;
        }
        if (this->data[this->heapAndFreeStack[lesserChild]] < 
        this->data[this->heapAndFreeStack[ndx]]) {
            swap(this->heapAndFreeStack[lesserChild], this->heapAndFreeStack[ndx]);
            this->bubbleDown(lesserChild);
        }
    }*/
    int child1 = (ndx * 2) + 1;
    int child2 = (ndx * 2) + 2;
    if (child1 < this->numItems) {
        int lesserChild = child1;
        if ((child2 < this->numItems) && (this->data[child2] < this->data[child1])) {
            lesserChild = child2;
        }
        if (this->data[lesserChild] < this->data[ndx]) {
            swap(this->data[lesserChild], this->data[ndx]);
            swap(this->heapAndFreeStack[lesserChild], this->heapAndFreeStack[ndx]);
            this->bubbleDown(lesserChild);
        }
    }
}

/**
 * doubleCapacity
 *
 * Doubles the capacity of the heap. The data and heapAndFreeStack arrays
 * are copied to new arrays of double the capacity. The old arrays are
 * deleted.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template <typename T>
void ArrayHeap<T>::doubleCapacity() {
    this->capacity *= 2;
    T *tempData = new T[this->capacity];
    int *tempHeapAndFreeStack = new int[this->capacity];
    for(int i = 0; i < this->numItems; i++) {
        tempData[i] = this->data[i];
        tempHeapAndFreeStack[i] = this->heapAndFreeStack[i];
    }
    delete [] this->data;
    delete [] this->heapAndFreeStack;
    this->data = tempData;
    this->heapAndFreeStack = tempHeapAndFreeStack;
}


#endif

