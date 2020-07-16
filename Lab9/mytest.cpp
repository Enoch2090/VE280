//
// Created by cyx on 20-6-12.
//

#include <iostream>
#include "mylist.h"

int main()
{

    try
    {
        List<int> la, lb;
        la.insertBack(9);
        la.insertBack(7);
        la.insertBack(4);
        la.print();

        lb.insertBack(0);
        lb.insertBack(0);
        lb.insertBack(0);
        lb.insertBack(1);
        lb.print();

        std::cout << isLarger(la, lb) << '\n';

        List<int> le = Add(la, lb);
        le.print();

        List<int> ab_sum(la);
        ab_sum.print();
        ab_sum = Add(la, lb);
        ab_sum.print();

        List<bool> lc;
        lc.insertBack(true);
        lc.insertBack(false);
        lc.insertBack(true);
        lc.print();

        List<bool> ld(lc);
        ld.removeFront();
        ld.print();
    }
    catch (emptyList)
    {
        std::cout << "Remove from empty list!\n";
    }

    return 0;
}
