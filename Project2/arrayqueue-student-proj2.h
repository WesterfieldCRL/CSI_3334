#ifndef ARRAY_QUEUE_STUDENT_PROJ2_H
#define ARRAY_QUEUE_STUDENT_PROJ2_H

#include "arrayqueue-prof-proj2.h"
#include <cassert>

template <class Base>
ArrayQueue<Base>::ArrayQueue()
{
    this->capacity = 1;
    this->length = 1;
    this->front = 0;
    this->data = new Base[this->capacity];
}

template <class Base>
ArrayQueue<Base>::ArrayQueue(const ArrayQueue<Base> &q)
{
    this->data = new Base[q.capacity];
    this->length = q.length;
    this->capacity = q.capacity;

    for (int i = 0; i < q.capacity; i++)
    {
        this->data[i] = q.data[i];
    }
}

template <class Base>
ArrayQueue<Base>::~ArrayQueue()
{
    delete [] this->data;
}

template <class Base>
void ArrayQueue<Base>::add(const Base &item)
{

}

template <class Base>
void ArrayQueue<Base>::remove()
{

}

template <class Base>
const Base &ArrayQueue<Base>::getFront() const
{
    return this->data[this->front];
}

template <class Base>
int ArrayQueue<Base>::getLength() const
{
    return this->length;
}

template <class Base>
const ArrayQueue<Base> &ArrayQueue<Base>::operator=(const ArrayQueue<Base> &q)
{

}


#endif