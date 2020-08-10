#include <iostream>
#include <map>
using namespace std;

void NAME()
{
    int *a = new int(10);
    int *b = new int(20);
    int *c = nullptr;
    int *d = nullptr;
    cout << (a && (*a == 10)) << endl;
    cout << (b && (*b == 10)) << endl;
    cout << (c && (*c == 10)) << endl;
    cout << ((*d == 10) && d) << endl;
}

int main()
{
    NAME();
    return 0;
}