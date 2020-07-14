#include <iostream>
#include <cassert>
#include "binaryTree.h"
using namespace std;

int main()
{
    Node *n1 = new Node("a", 4);
    Node *n2 = new Node("bb", 2);
    Node *n3 = new Node("ddd", 5);
    Node *n4 = new Node("e", 7);
    Node *n5 = new Node("c", 3);
    n3->setleft(n4);
    n3->setright(n5);
    n1->setleft(n2);
    n1->setright(n3);
    cout << n1->leftSubtree()->getnum() << endl;
    cout << n1->rightSubtree()->leftSubtree()->getnum() << endl;
    Node *n6 = Node::mergeNodes(n1, n2);
    cout << n6->getnum() << " " << n6->getstr() << endl;
    cout << n6->leftSubtree()->getnum() << " " << n6->leftSubtree()->getstr() << endl;
    cout << n6->rightSubtree()->getnum() << " " << n6->rightSubtree()->getstr() << endl;
    delete n6;
}