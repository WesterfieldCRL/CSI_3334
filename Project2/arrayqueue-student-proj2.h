#ifndef ARRAY_QUEUE_STUDENT_PROJ2_H
#define ARRAY_QUEUE_STUDENT_PROJ2_H

#include "arrayqueue-prof-proj2.h"
#include <cassert>

template <class Base>
ArrayQueue<Base>::ArrayQueue()
{
    this->capacity = 2;
    this->length = 0;
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
    if (this != &q)
    {
        delete [] this->data;
        this->capacity = q.capacity;
        this->length = q.length;
        this->front = q.front;

        this->data = new Base[this->capacity];

        for (int i = 0; i < this->capacity; i++)
        {
            this->data[i] = q.data[i];
        }
    }
    return this;
}

template <class Base>
void ArrayQueue<Base>::doubleCapacity()
{
    this->capacity *= 2;
    Base *temp = this->data;
    this->data = new Base[this->capacity];

    for (int i = 0; i < this->capacity; i++)
    {
        this->data[i] = temp[i];
    }
    delete [] temp;
}


#endif