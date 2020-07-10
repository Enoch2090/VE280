#include <iostream>
#include "binaryTree.h"
using namespace std;

int main()
{
    Node n1("a", 0);
    Node n2("b", 1);
    Node n3("c", 2);
    Node n4("d", 3);
    Node n5("e", 4);
    n3.setleft(&n4);
    n3.setright(&n5);
    n1.setleft(&n2);
    n1.setright(&n3);
    cout << n1.leftSubtree()->getnum() << endl;
    cout << n1.rightSubtree()->leftSubtree()->getnum() << endl;
}