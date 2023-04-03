#ifndef ARRAY_HEAP_PROJ5_STUDENT_H
#define ARRAY_HEAP_PROJ5_STUDENT_H

#include "arrayheap-prof-proj5.h"
#include <algorithm>

using namespace std;

template <typename T>
ArrayHeap<T>::ArrayHeap()
{

}

template <typename T>
ArrayHeap<T>::ArrayHeap(ArrayHeap<T> const &h)
{

}

template <typename T>
ArrayHeap<T>::~ArrayHeap()
{

}

template <typename T>
ArrayHeap<T> const &ArrayHeap<T>::operator=(ArrayHeap<T> const &ah)
{

}

template <typename T>
void ArrayHeap<T>::insert(T const &item)
{

}

template <typename T>
void ArrayHeap<T>::removeMinItem()
{

}

template <typename T>
T const &ArrayHeap<T>::getMinItem() const
{

}

template <typename T>
int ArrayHeap<T>::getNumItems() const
{

}

void bubbleUp(int ndx);
void bubbleDown(int ndx);


#endif

