#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H
#include "dlist.h"
#include <iostream>

template <class T>
bool Dlist<T>::isEmpty() const
{
    return !(this->first);
}

template <class T>
void Dlist<T>::insertFront(T *op)
{
    node *newnode = new node;
    newnode->op = op;
    if (!this->first)
    {
        newnode->prev = nullptr;
        newnode->next = nullptr;
        this->first = newnode;
        this->last = newnode;
    }
    else
    {
        newnode->next = this->first;
        newnode->prev = nullptr;
        this->first->prev = newnode;
        this->first = newnode;
    }
}

template <class T>
void Dlist<T>::insertBack(T *op)
{
    node *newnode = new node;
    newnode->op = op;
    if (!this->last)
    {
        newnode->prev = nullptr;
        newnode->next = nullptr;
        this->first = newnode;
        this->last = newnode;
    }
    else
    {
        newnode->next = nullptr;
        newnode->prev = this->last;
        this->last->next = newnode;
        this->last = newnode;
    }
}

template <class T>
T *Dlist<T>::removeFront()
{
    T *valp;
    if (this->isEmpty())
    {
        emptyList E;
        throw E;
    }
    else
    {
        if (this->first == this->last)
        {
            // Only one node
            valp = this->first->op;
            delete this->first;
            this->first = nullptr;
            this->last = nullptr;
        }
        else
        {
            valp = this->first->op;
            node *newFirst = this->first->next;
            newFirst->prev = nullptr;
            delete this->first;
            this->first = newFirst;
        }
    }
    return valp;
}

template <class T>
T *Dlist<T>::removeBack()
{
    T *valp;
    if (this->isEmpty())
    {
        emptyList E;
        throw E;
    }
    else
    {
        if (this->first == this->last)
        {
            // Only one node
            valp = this->first->op;
            delete this->first;
            this->first = nullptr;
            this->last = nullptr;
        }
        else
        {
            valp = this->last->op;
            node *newLast = this->last->prev;
            newLast->next = nullptr;
            delete this->last;
            this->last = newLast;
        }
    }
    return valp;
}

template <class T>
T *Dlist<T>::remove(bool (*cmp)(const T *, const T *), T *ref)
{
    node *current = this->first;
    T *valp;
    while (current)
    {
        if (cmp(current->op, ref))
        {
            valp = current->op;
            if (!current->prev)
            {
                // Current is the first element
                this->first = current->next;
                if (current->next)
                {
                    current->next->prev = nullptr;
                }
            }
            if (!current->next)
            {
                // Current is the last element
                this->last = current->prev;
                if (current->prev)
                {
                    current->prev->next = nullptr;
                }
            }
            if (current->prev && current->next)
            {
                // Current is an ordinary middle element
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            return valp;
        }
        current = current->next;
    }
    return nullptr;
}

template <class T>
Dlist<T>::Dlist()
{
    this->first = nullptr;
    this->last = nullptr;
}

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l)
{
    this->first = nullptr;
    this->last = nullptr;
    node *current = l.first;
    while (current)
    {
        T *newop = new T;
        *newop = *(current->op);
        this->insertBack(newop);
        current = current->next;
    }
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l)
{
    node *thisCurrent = this->first;
    node *thisNext;
    while (thisCurrent)
    {
        delete thisCurrent->op;
        thisNext = thisCurrent->next;
        delete thisCurrent;
        thisCurrent = thisNext;
    }
    node *current = l.first;
    while (current)
    {
        T *newop = new T;
        *newop = *(current->op);
        this->insertBack(newop);
        current = current->next;
    }
    return (*this);
}

template <class T>
Dlist<T>::~Dlist()
{
    node *thisCurrent = this->first;
    node *thisNext;
    while (thisCurrent)
    {
        delete thisCurrent->op;
        thisNext = thisCurrent->next;
        delete thisCurrent;
        thisCurrent = thisNext;
    }
}

#endif //DLIST_IMPL_H