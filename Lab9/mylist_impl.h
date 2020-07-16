//
// Created by cyx on 20-5-29.
//

#ifndef INTLIST_IMPL_H
#define INTLIST_IMPL_H

#include <iostream>

#include <stack>
#include "mylist.h"

template <class T>
void List<T>::print()
{
    node_t<T> *itr = first;
    while (itr)
    {
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
void List<T>::removeAll()
{
    if (this->first == this->last)
    {
        delete first;
    }
    else
    {
        node_t<T> *victim = this->first;
        node_t<T> *next;
        while (victim != nullptr)
        {
            next = victim->next;
            delete victim;
            victim = next;
        }
    }
    this->first = nullptr;
    this->last = nullptr;
}

template <class T>
void List<T>::copyFrom(const List &l)
{
    if (this->first != nullptr)
    {
        this->removeAll();
    }
    if (l.first != nullptr)
    {
        node_t<T> *next = l.first;
        while (next != nullptr)
        {
            this->insertBack(next->val);
            next = next->next;
        }
    }
}

template <class T>
bool List<T>::isEmpty() const
{
    return (this->first == nullptr);
}

template <class T>
void List<T>::insertBack(T val)
{
    node_t<T> *newNode = new node_t<T>;
    newNode->val = val;
    newNode->next = nullptr;
    if (this->last != nullptr)
    {
        this->last->next = newNode;
    }
    if (this->first == nullptr)
    {
        this->first = newNode;
    }
    this->last = newNode;
}

template <class T>
T List<T>::removeFront()
{
    if (this->first == nullptr)
    {
        emptyList e;
        throw e;
    }
    else
    {
        T val = this->first->val;
        node_t<T> *second = this->first->next;
        delete this->first;
        this->first = second;
        if (second == nullptr || second->next == nullptr)
        {
            this->last = second;
        }
        return val;
    }
}

template <class T>
const node_t<T> *List<T>::returnHead() const
{
    return (this->first);
}

template <class T>
List<T>::List()
{
    this->first = nullptr;
    this->last = nullptr;
}

template <class T>
List<T>::~List()
{
    node_t<T> *Paul = this->first;
    node_t<T> *nextPaul;
    while (Paul != nullptr)
    {
        nextPaul = Paul->next;
        delete Paul;
        Paul = nextPaul;
    }
}

template <class T>
List<T>::List(const List<T> &l)
{
    this->first = nullptr;
    this->last = nullptr;
    this->copyFrom(l);
}

template <class T>
List<T> &List<T>::operator=(const List<T> &l)
{
    this->copyFrom(l);
    return *this;
}

bool isLarger(const List<int> &a, const List<int> &b)
{
    List<int> _a;
    List<int> _b;
    _a = a;
    _b = b;
    if (_a.isEmpty())
    {
        _a.insertBack(0);
    }
    if (_b.isEmpty())
    {
        _b.insertBack(0);
    }
    int len1 = 0;
    int len2 = 0;
    const node_t<int> *node1 = _a.returnHead();
    const node_t<int> *node2 = _b.returnHead();
    while (node1 != nullptr)
    {
        len1++;
        node1 = node1->next;
    }
    while (node2 != nullptr)
    {
        len2++;
        node2 = node2->next;
    }
    if (len1 != len2)
    {
        return (len1 > len2);
    }
    else
    {
        node1 = _a.returnHead();
        node2 = _b.returnHead();
        std::stack<int> aNum;
        std::stack<int> bNum;

        while (node1 != nullptr)
        {
            aNum.push(node1->val);
            bNum.push(node2->val);
            node1 = node1->next;
            node2 = node2->next;
        }
        while (!aNum.empty())
        {
            if (aNum.top() > bNum.top())
            {
                return true;
            }
            else if (aNum.top() < bNum.top())
            {
                return false;
            }
            aNum.pop();
            bNum.pop();
        }
    }
    return false; // Silence the compiler.
}

List<int> Add(const List<int> &a, const List<int> &b)
{
    if (a.isEmpty() || b.isEmpty())
    {
        return (a.isEmpty() && b.isEmpty()) ? List<int>(a) : (a.isEmpty() ? List<int>(b) : List<int>(a));
    }
    else
    {
        const node_t<int> *node1 = a.returnHead();
        const node_t<int> *node2 = b.returnHead();
        List<int> sum;
        int carry = 0;
        int thisSum = 0;
        while (node1 != nullptr || node2 != nullptr)
        {
            if (node1 != nullptr && node2 != nullptr)
            {
                thisSum = node1->val + node2->val + carry;
                carry = 0;
                if (thisSum >= 10)
                {
                    thisSum -= 10;
                    carry = 1;
                }
                sum.insertBack(thisSum);
                node1 = node1->next;
                node2 = node2->next;
            }
            else if (node1 == nullptr && node2 != nullptr)
            {
                thisSum = node2->val + carry;
                carry = 0;
                if (thisSum >= 10)
                {
                    thisSum -= 10;
                    carry = 1;
                }
                sum.insertBack(thisSum);
                node2 = node2->next;
            }
            else if (node1 != nullptr && node2 == nullptr)
            {
                thisSum = node1->val + carry;
                carry = 0;
                if (thisSum >= 10)
                {
                    thisSum -= 10;
                    carry = 1;
                }
                sum.insertBack(thisSum);
                node1 = node1->next;
            }
        }
        if (carry == 1)
        {
            sum.insertBack(1);
        }
        return sum;
    }
}

#endif //INTLIST_IMPL_H
