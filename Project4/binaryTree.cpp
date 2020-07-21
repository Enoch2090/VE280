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
void Node::setleft(Node *n)
{
    this->left = n;
}

Node *Node::rightSubtree() const
{
    return this->right;
}

void Node::setright(Node *n)
{
    this->right = n;
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
    Node *mergedNode = new Node(mergedStr, mergedNum, leftNode, rightNode);
    return mergedNode;
}

/* =============================== Helper Functions for The Binary Tree. =============================== */
void free_helper(Node *node)
{
    Node *left = node->leftSubtree();
    Node *right = node->rightSubtree();
    if (left)
    {
        free_helper(left);
    }
    if (right)
    {
        free_helper(right);
    }
    delete node;
}

bool findPathHelper_isPath(Node *node, const string &s)
{
    if (!node)
    {
        return false;
    }
    if (node->getstr() == s)
    {
        return true;
    }
    if (node->leftSubtree())
    {
        if (findPathHelper_isPath(node->leftSubtree(), s))
        {
            return true;
        }
    }
    if (node->rightSubtree())
    {
        if (findPathHelper_isPath(node->rightSubtree(), s))
        {
            return true;
        }
    }
    return false;
}

string findPathHelper_createString(Node *node, const string &s)
{
    if (node)
    {
        if (findPathHelper_isPath(node->leftSubtree(), s))
        {
            return "0" + findPathHelper_createString(node->leftSubtree(), s);
        }
        else if (findPathHelper_isPath(node->rightSubtree(), s))
        {
            return "1" + findPathHelper_createString(node->rightSubtree(), s);
        }
        else
        {
            return "";
        }
    }
    else
    {
        return "";
    }
}
void preorder_num_print(Node *node)
{
    if (node)
    {
        cout << node->getnum() << " ";
        if (node->leftSubtree())
        {
            preorder_num_print(node->leftSubtree());
        }
        if (node->rightSubtree())
        {
            preorder_num_print(node->rightSubtree());
        }
    }
}

void inorder_str_print(Node *node)
{
    if (node)
    {
        if (node->leftSubtree())
        {
            inorder_str_print(node->leftSubtree());
        }
        cout << node->getstr() << " ";
        if (node->rightSubtree())
        {
            inorder_str_print(node->rightSubtree());
        }
    }
}

void postorder_num_print(Node *node)
{
    if (node)
    {
        if (node->leftSubtree())
        {
            postorder_num_print(node->leftSubtree());
        }
        if (node->rightSubtree())
        {
            postorder_num_print(node->rightSubtree());
        }
        cout << node->getnum() << " ";
    }
}

bool path_sum_gt(Node *node, int sum)
{
    if (!node)
    {
        return false;
    }
    else
    {
        if (!node->leftSubtree() && node->rightSubtree())
        {
            return path_sum_gt(node->rightSubtree(), sum - node->getnum());
        }
        else if (!node->rightSubtree() && node->leftSubtree())
        {
            return path_sum_gt(node->leftSubtree(), sum - node->getnum());
        }
        else if (node->rightSubtree() && node->leftSubtree())
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
    if (!node2)
    {
        return true;
    }
    else if (!node1)
    {
        return false;
    }
    else if (node1->getnum() == node2->getnum())
    {
        return covered(node1->leftSubtree(), node2->leftSubtree()) && covered(node1->rightSubtree(), node2->rightSubtree());
    }
    else
    {
        return false;
    }
}

bool contained(Node *node1, Node *node2)
{
    if (!node1 && !node2)
    {
        return true;
    }
    else if (!node1 || !node2)
    {
        return false;
    }
    else
    {
        return covered(node1, node2) || contained(node1->leftSubtree(), node2) || contained(node1->rightSubtree(), node2);
    }
}

Node *copy_helper(Node *n)
{
    Node *new_node = nullptr;
    if (n)
    {
        Node *new_left = n->leftSubtree();
        Node *new_right = n->rightSubtree(); // Set for nullptr.
        if (n->leftSubtree())
        {
            new_left = copy_helper(n->leftSubtree());
        }
        if (n->rightSubtree())
        {
            new_right = copy_helper(n->rightSubtree());
        }
        new_node = new Node(n->getstr(), n->getnum(), new_left, new_right);
    }
    return new_node;
}
int depth_helper(Node *n)
{
    int depth = 0;
    if (n)
    {
        int depth_left = (!n->leftSubtree()) ? (0) : (depth_helper(n->leftSubtree()));
        int depth_right = (!n->rightSubtree()) ? (0) : (depth_helper(n->rightSubtree()));
        int sub_depth = (depth_left > depth_right) ? depth_left : depth_right;
        depth = sub_depth == 0 ? 1 : sub_depth + 1;
    }
    return depth;
}

int sum_helper(Node *n)
{
    if (n)
    {
        int sum = n->getnum();
        if (n->leftSubtree())
        {
            sum += sum_helper(n->leftSubtree());
        }
        if (n->rightSubtree())
        {
            sum += sum_helper(n->rightSubtree());
        }
        return sum;
    }
    return 0;
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode)
{
    this->root = rootNode;
}

BinaryTree::~BinaryTree()
{
    free_helper(this->root);
}

string BinaryTree::findPath(const string &s) const
{
    string res = findPathHelper_createString(this->root, s);
    return res == "" ? (this->root->getstr() == s ? "" : "-1") : res;
}

int BinaryTree::sum() const
{
    if (this->root)
    {
        return sum_helper(this->root);
    }
    else
    {
        return 0;
    }
}

int BinaryTree::depth() const
{
    return depth_helper(this->root);
}

void BinaryTree::preorder_num() const
{
    if (this->root)
    {
        preorder_num_print(this->root);
        cout << endl;
    }
}

void BinaryTree::inorder_str() const
{
    if (this->root)
    {
        inorder_str_print(this->root);
        cout << endl;
    }
}

void BinaryTree::postorder_num() const
{
    if (this->root)
    {
        postorder_num_print(this->root);
        cout << endl;
    }
}

bool BinaryTree::allPathSumGreater(int temp) const
{
    return path_sum_gt(this->root, temp);
}

bool BinaryTree::covered_by(const BinaryTree &tree) const
{
    return covered(tree.root, this->root);
}

bool BinaryTree::contained_by(const BinaryTree &tree) const
{
    return contained(tree.root, this->root);
}

BinaryTree BinaryTree::copy() const
{
    Node *new_root = copy_helper(this->root);
    return BinaryTree(new_root);
}
