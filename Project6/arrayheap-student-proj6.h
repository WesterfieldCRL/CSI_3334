#ifndef ARRAY_HEAP_STUDENT_PROJ6_H
#define ARRAY_HEAP_STUDENT_PROJ6_H

#include "arrayheap-prof-proj6.h"
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
ArrayHeap<T>::ArrayHeap()
{
    this->capacity = 10;
    this->numItems = 0;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];
    this->dataToHeap = new int[this->capacity];
    for (int i = 0; i < this->capacity; i++)
    {
        this->heapAndFreeStack[i] = -1;
        this->dataToHeap[i] = -1;
    }
}

template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h)
{
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

template <typename T>
ArrayHeap<T>::~ArrayHeap()
{
    delete [] this->data;
    delete [] this->heapAndFreeStack;
    delete [] this->dataToHeap;
    this->capacity = 0;
    this->numItems = 0;
}

template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah)
{
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
}

template <typename T>
int ArrayHeap<T>::insert(T const &item)
{
    if(this->numItems >= this->capacity) {
        this->doubleCapacity();
    }

    for (int i = 0; i < this->capacity; i++)
    {
        if (this->dataToHeap[i] == -1)
        {
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
 
template <typename T>
void ArrayHeap<T>::removeMinItem()
{
    if(this->numItems <= 0) {
        return;
    }

    this->dataToHeap[this->heapAndFreeStack[this->numItems - 1]] = 0;
    this->dataToHeap[this->heapAndFreeStack[0]] = -1;
    
    this->heapAndFreeStack[0] = this->heapAndFreeStack[this->numItems - 1];
    this->numItems--;
    this->bubbleDown(0);
}

template <typename T>
T const &ArrayHeap<T>::getMinItem() const
{
    return this->data[this->heapAndFreeStack[0]];
}

template <typename T>
int ArrayHeap<T>::getNumItems() const
{
    return this->numItems;
}

template <typename T>
bool ArrayHeap<T>::isOnHeap(int key) const
{
    bool isOnHeap = false;
    if(this->dataToHeap[key] != -1) {
        isOnHeap = true;
    }
    return isOnHeap;
}

template <typename T>
void ArrayHeap<T>::changeItemAtKey(int key, T const &newItem)
{
    if(this->dataToHeap[key] == -1) {
        return;
    }

    this->data[this->heapAndFreeStack[this->dataToHeap[key]]] = newItem;
    this->bubbleUp(this->heapAndFreeStack[this->dataToHeap[key]]);
    this->bubbleDown(this->heapAndFreeStack[this->dataToHeap[key]]);
}

template <typename T>
void ArrayHeap<T>::doubleCapacity()
{
    this->capacity *= 2;
    T *newData = new T[this->capacity];
    int *newHeapAndFreeStack = new int[this->capacity];
    int *newDataToHeap = new int[this->capacity];

    for (int i = 0; i < this->capacity; i++)
    {
        newData[i] = -1;
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

template <typename T>
void ArrayHeap<T>::bubbleUp(int ndx)
{
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

template <typename T>
void ArrayHeap<T>::bubbleDown(int ndx)
{
    int leftChild = (2 * ndx) + 1;
    int rightChild = (2 * ndx) + 2;
    int minChild = leftChild;

    if(leftChild >= this->numItems) {
        return;
    }

    if(rightChild < this->numItems && this->data[this->heapAndFreeStack[rightChild]] < this->data[this->heapAndFreeStack[leftChild]]) {
        minChild = rightChild;
    }

    if(this->data[this->heapAndFreeStack[ndx]] > this->data[this->heapAndFreeStack[minChild]]) {
        swap(this->heapAndFreeStack[ndx], this->heapAndFreeStack[minChild]);
        swap(this->dataToHeap[this->heapAndFreeStack[ndx]], this->dataToHeap[this->heapAndFreeStack[minChild]]);
        this->bubbleDown(minChild);
    }
}

#endif

