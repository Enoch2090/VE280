#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H
#include <iostream>
#include "dlist.h"

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
    if (!this->first)
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
            this->first = newLast;
        }
    }
    return valp;
}

// template <class T>
// bool cmp(const T *T1, const T *T2)
// {
//     return (*T1 == *T2);
// }

template <class T>
T *Dlist<T>::remove(bool (*cmp)(const T *, const T *), T *ref)
{
    node *current = this->first;
    T *valp = nullptr;
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
        }
    }
    return valp;
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
    node *current = l.first;
    while (current)
    {
        T *newop = new T;
        *newop = *(current->op);
        this->insertBack(newop);
    }
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l)
{
    node *thisCurrent = this->first;
    while (thisCurrent)
    {
        delete thisCurrent->op;
        node *thisNext = thisCurrent->next;
        delete thisCurrent;
        thisCurrent = thisNext;
    }
    node *current = l.first;
    while (current)
    {
        T *newop = new T;
        *newop = *(current->op);
        this->insertBack(newop);
    }
}

template <class T>
Dlist<T>::~Dlist()
{
    node *thisCurrent = this->first;
    while (thisCurrent)
    {
        delete thisCurrent->op;
        node *thisNext = thisCurrent->next;
        delete thisCurrent;
        thisCurrent = thisNext;
    }
}
#endif //DLIST_IMPL_H