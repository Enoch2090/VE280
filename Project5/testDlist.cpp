#include "dlist.h"
#include <iostream>
using namespace std;

// static bool compare(const int *i, const int *j)
// {
//     return *i == *j;
// }

void print(Dlist<int> &d, int size)
{
    for (int i = 0; i < size; i++)
    {
        int *currBlock = d.removeFront();
        cout << *currBlock << " ";
        d.insertBack(currBlock);
    }
    cout << endl;
}
int main(int argc, char *argv[])
{

    Dlist<int> ilist;
    int *ip = new int(5);
    ilist.insertFront(ip);
    int *ip2 = new int(2);
    ilist.insertFront(ip2);
    int *ip3 = new int(3);
    int *ip4 = new int(5);
    ilist.insertFront(ip3);
    ilist.insertBack(ip4);
    print(ilist, 4);
    ip = ilist.removeFront();
    cout << *ip << endl;
    print(ilist, 2);
    cout << ilist.isEmpty() << endl;
    delete ip;
    // ip2 = ilist.remove(compare, ip4);
    // cout << *ip2 << endl;
    // delete ip2;
    return 0;
}
