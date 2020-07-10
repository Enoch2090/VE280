#include <iostream>
#include "binaryTree.h"
using namespace std;

int main()
{
    Node *n1 = new Node("a", 0);
    Node *n2 = new Node("b", 1);
    Node *n3 = new Node("c", 2);
    Node *n4 = new Node("d", 3);
    Node *n5 = new Node("e", 4);
    n3->setleft(n4);
    n3->setright(n5);
    n1->setleft(n2);
    n1->setright(n3);
    Node *n0 = new Node("A", -1);
    BinaryTree b(n0);
    n0->setright(n1);
    cout << b.depth() << endl;
    cout << b.findPath("A") << endl;
}