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
    Node *n6 = new Node("5", 8);
    Node *n7 = new Node("5", 9);
    n2->setleft(n4);
    n2->setright(n5);
    n1->setleft(n2);
    n1->setright(n3);
    BinaryTree b(n1);
    b.inorder_str();
    cout << endl;
    n5->setleft(n6);
    n5->setright(n7);

    cout << b.depth() << endl;
    cout << b.findPath("4") << endl;
    b.preorder_num();
    cout << endl;
    b.inorder_str();
    cout << endl;
    b.postorder_num();
    cout << endl;
    // BinaryTree b1(n2);
    // assert(b.allPathSumGreater(0) == 1);
    // assert(b.allPathSumGreater(12) == 0);
    // assert(b1.contained_by(b) == 1);
    // assert(b1.covered_by(b) == 0);
}
