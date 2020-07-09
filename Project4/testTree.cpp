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
    n1.setleft(&n3);
    BinaryTree b(&n1);
    cout << b.findPath("a");
}