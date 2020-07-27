#include <iostream>
#include "dlist.h"
using namespace std;

char topOfChar(Dlist<char> &cDlist)
{
    cout << "kfgkg" << endl;

    if (cDlist.isEmpty())
    {
        return 'N';
    }
    cout << "dasd" << endl;
    char *topChar = cDlist.removeFront();
    cout << *topChar << endl;
    cDlist.insertFront(topChar);
    return *topChar;
}
int main()
{
    Dlist<char> d;
    char *a = new char('a');
    char *b = new char('b');
    d.insertFront(a);
    d.insertBack(b);
    cout << topOfChar(d) << endl;
    return 0;
}