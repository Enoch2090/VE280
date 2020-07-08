#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right)
{
    this->str = str;
    this->num = num;
    this->left = left;
    this->right = right;
}

Node *Node::leftSubtree() const
{
    return this->left;
}

Node *Node::rightSubtree() const
{
    return this->right;
}

string Node::getstr() const
{
    return this->str;
}

int Node::getnum() const
{
    return this->num;
}
void Node::incnum()
{
    this->num++;
}
Node *Node::mergeNodes(Node *leftNode, Node *rightNode)
{
    string mergedStr = leftNode->getstr() + rightNode->getstr();
    int mergedNum = leftNode->getnum() + rightNode->getnum();
    Node *mergedNode = new Node(mergedStr, mergedNum);
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode)
{
    if (rootNode == nullptr)
    {
        Node *rootNode = new Node("", 0);
    }
    else
    {
        this->root = rootNode;
    }
}

BinaryTree::~BinaryTree()
{
    // TODO: implement this function.
}

string BinaryTree::findPath(const string &s) const
{
    // TODO: dasdasdas
}

int BinaryTree::sum() const
{
    // TODO: implement this function.
}

int BinaryTree::depth() const
{
    // TODO: implement this function.
}

void BinaryTree::preorder_num() const
{
    // TODO: implement this function.
}

void BinaryTree::inorder_str() const
{
    // TODO: implement this function.
}

void BinaryTree::postorder_num() const
{
    // TODO: implement this function.
}

bool BinaryTree::allPathSumGreater(int temp) const
{
    // TODO: implement this function.
}

bool BinaryTree::covered_by(const BinaryTree &tree) const
{
    // TODO: implement this function.
}

bool BinaryTree::contained_by(const BinaryTree &tree) const
{
    // TODO: implement this function.
}

BinaryTree BinaryTree::copy() const
{
    // TODO: implement this function.
}
