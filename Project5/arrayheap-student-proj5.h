#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>

using namespace std;

template <typename T>
ArrayHeap<T>::ArrayHeap()
{
    this->capacity = 10;
    this->numItems = 0;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];
}

template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h)
{
    this->capacity = h.capacity;
    this->numItems = h.numItems;
    this->data = new T[this->capacity];
    this->heapAndFreeStack = new int[this->capacity];
    for(int i = 0; i < this->capacity; i++)
    {
        this->data[i] = h.data[i];
        this->heapAndFreeStack[i] = h.heapAndFreeStack[i];
    }
}

template <typename T>
ArrayHeap<T>::~ArrayHeap()
{
    delete [] this->data;
    delete [] this->heapAndFreeStack;
    this->capacity = 0;
    this->numItems = 0;
}

template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah)
{
    if(this != &ah)
    {
        this->capacity = ah.capacity;
        this->numItems = ah.numItems;
        this->data = new T[this->capacity];
        this->heapAndFreeStack = new int[this->capacity];
        for(int i = 0; i < this->capacity; i++)
        {
            this->data[i] = ah.data[i];
            this->heapAndFreeStack[i] = ah.heapAndFreeStack[i];
        }
    }
    return *this;
}

template <typename T>
void ArrayHeap<T>::insert(T const &item)
{
    if(this->numItems == this->capacity)
    {
        this->doubleCapacity();
    }
    this->data[this->numItems] = item;
    this->heapAndFreeStack[this->numItems] = this->numItems;
    this->numItems++;
    this->bubbleUp(this->numItems - 1);
}

template <typename T>
void ArrayHeap<T>::removeMinItem()
{

}

template <typename T>
T const &ArrayHeap<T>::getMinItem() const
{
    return this->data[0];
}

template <typename T>
int ArrayHeap<T>::getNumItems() const
{
    return this->numItems;
}

template <typename T>
void bubbleUp(int ndx)
{
    if (ndx == 0)
    {
        return;
    }
    int parent = (ndx - 1) / 2;
    if (this->data[ndx] < this->data[parent])
    {
        swap(this->data[ndx], this->data[parent]);
        this->bubbleUp(parent);
    }
}

template <typename T>
void bubbleDown(int ndx)
{
    int child1 = (ndx * 2) + 1;
    int child2 = (ndx * 2) + 2;
    if (child1 < this->numItems)
    {
        int lesserChild = this->child1;
        if ((this->child2 < this->numItems) && (this->data[child2] < this->data[ndx]))
        {
            lesserChild = this->child2;
        }
        if (this->data[lesserChild] < this->data[ndx])
        {
            swap(this->data[lesserChild], this->data[ndx]);
            this->bubbleDown(lesserChild);
        }
        
    }
}


#endif

