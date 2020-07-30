#include "dlist.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);
    ilist.insertFront(ip);
    int *ip2 = new int(2);
    ilist.insertFront(ip2);
    int *ip3 = new int(3);
    ilist.insertFront(ip3);
    ip = ilist.removeFront();
    if (*ip != 1)
        result = -1;

    if (!ilist.isEmpty())
        result = -1;
    delete ip;
    delete ip2;
    delete ip3;
    return result;
}
