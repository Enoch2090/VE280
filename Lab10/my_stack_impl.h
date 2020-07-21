/*
 * This is an exercise of VE280 Lab 10, SU2020.
 * Written by Martin Ma.
 * Latest Update: 7/17/2020.
 * Copyright © 2020 Mars-tin. All rights reserved.
 */

#ifndef MY_STACK_IMPL_H
#define MY_STACK_IMPL_H

#include <iostream>
#include "my_stack.h"


template <class T>
void Stack<T>::print()
{
    Node<T>* itr = head;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}


#endif //MY_STACK_IMPL_H