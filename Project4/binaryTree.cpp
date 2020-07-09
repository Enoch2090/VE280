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

/* =============================== Helper Functions for The Binary Tree. =============================== */
void free_helper(Node *node)
{
    Node *left = node->leftSubtree();
    Node *right = node->rightSubtree();
    if (left != nullptr)
    {
        free_helper(left);
    }
    if (right != nullptr)
    {
        free_helper(right);
    }
    delete node;
}

bool findPathHelper_isPath(Node *node, const string &s)
{
    if (node->getstr() == s)
    {
        return true;
    }
    else
    {
        return ((node->leftSubtree() != nullptr) && (findPathHelper_isPath(node->leftSubtree(), s))) || ((node->rightSubtree() != nullptr) && (findPathHelper_isPath(node->rightSubtree(), s)));
        // TODO: Test null subtree.
    }
}

string findPathHelper_createString(Node *node, const string &s)
{
    if (findPathHelper_isPath(node->leftSubtree(), s))
    {
        return findPathHelper_createString(node->leftSubtree(), s) + "0";
    }
    else if (findPathHelper_isPath(node->leftSubtree(), s))
    {
        return findPathHelper_createString(node->rightSubtree(), s) + "1";
    }
    return "";
}
void preorder_num_print(Node *node)
{
    if (node != nullptr)
    {
        cout << node->getnum() << " ";
        if (node->leftSubtree() != nullptr)
        {
            preorder_num_print(node->leftSubtree());
        }
        if (node->rightSubtree() != nullptr)
        {
            preorder_num_print(node->rightSubtree());
        }
    }
}

void inorder_str_print(Node *node)
{
    if (node != nullptr)
    {
        if (node->leftSubtree() != nullptr)
        {
            inorder_str_print(node->leftSubtree());
        }
        cout << node->getstr() << " ";
        if (node->rightSubtree() != nullptr)
        {
            inorder_str_print(node->rightSubtree());
        }
    }
}

void postorder_num_print(Node *node)
{
    if (node != nullptr)
    {
        if (node->leftSubtree() != nullptr)
        {
            preorder_num_print(node->leftSubtree());
        }
        if (node->rightSubtree() != nullptr)
        {
            preorder_num_print(node->rightSubtree());
        }
        cout << node->getnum() << " ";
    }
}

bool path_sum_gt(Node *node, int sum)
{
    if (node == nullptr)
    {
        return false;
    }
    else
    {
        if (node->leftSubtree() == nullptr && node->rightSubtree() != nullptr)
        {
            return path_sum_gt(node->rightSubtree(), sum - node->getnum());
        }
        else if (node->rightSubtree() == nullptr && node->leftSubtree() != nullptr)
        {
            return path_sum_gt(node->leftSubtree(), sum - node->getnum());
        }
        else if (node->rightSubtree() != nullptr && node->leftSubtree() != nullptr)
        {
            return path_sum_gt(node->rightSubtree(), sum - node->getnum()) && path_sum_gt(node->leftSubtree(), sum - node->getnum());
        }
        else
        {
            return node->getnum() > sum;
        }
    }
}

bool covered(Node *node1, Node *node2)
{
    // TODO: nullptrs
    if (node1->getnum() == node2->getnum())
    {
        return covered(node1->leftSubtree(), node2->leftSubtree());
    }
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
    free_helper(this->root);
}

string BinaryTree::findPath(const string &s) const
{
    return findPathHelper_createString(this->root, s);
}

int BinaryTree::sum() const
{
    int sum = this->root->getnum();
    if (this->root->leftSubtree() != nullptr)
    {
        BinaryTree Left = BinaryTree(this->root->leftSubtree());
        sum += Left.sum();
    }
    if (this->root->rightSubtree() != nullptr)
    {
        BinaryTree Right = BinaryTree(this->root->rightSubtree());
        sum += Right.sum();
    }
    return sum;
}

int BinaryTree::depth() const
{
    int depth = 0;
    BinaryTree Left = BinaryTree(this->root->leftSubtree());
    int depth_left = (this->root->leftSubtree() == nullptr) ? (0) : (Left.depth());
    BinaryTree Right = BinaryTree(this->root->rightSubtree());
    int depth_right = (this->root->rightSubtree() == nullptr) ? (0) : (Right.depth());
    int sub_depth = (depth_left > depth_right) ? depth_left : depth_right;
    depth = sub_depth == 0 ? 1 : sub_depth + 1;
}

void BinaryTree::preorder_num() const
{
    if (this->root != nullptr)
    {
        preorder_num_print(this->root);
    }
}

void BinaryTree::inorder_str() const
{
    if (this->root != nullptr)
    {
        inorder_str_print(this->root);
    }
}

void BinaryTree::postorder_num() const
{
    if (this->root != nullptr)
    {
        postorder_num_print(this->root);
    }
}

bool BinaryTree::allPathSumGreater(int temp) const
{
    return path_sum_gt(this->root, temp);
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
