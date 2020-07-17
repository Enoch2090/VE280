#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
Node::Node(const std::string &str, int num, Node *left, Node *right) {      //whether the object that thee pointer exist
    // TODO: implement this function.
    this->str = str;
    this->num = num;
    this->left = left;
    this->right = right;
}

Node* Node::leftSubtree() const{
    // TODO: implement this function.
    return left;
}

void Node::setleft(Node *n) {
    // TODO: implement this function.
    this->left = n;
}

Node* Node::rightSubtree() const{
    // TODO: implement this function.
    return right;
}

void Node::setright(Node *n) {
    // TODO: implement this function.
    this->right = n;
}

string Node::getstr() const {
    // TODO: implement this function.
    return str;
}

int Node::getnum() const {
    // TODO: implement this function.
    return num;
}

void Node::incnum() {
    // TODO: implement this function.
    this->num++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
    // TODO: implement this function.
    std::string combination;
    combination = leftNode->str + rightNode->str;
    Node *p = new Node(combination, leftNode->num + rightNode->num);
    return p;
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode){
    // TODO: implement this function.
    this->root = rootNode;
}

void deletefunction(Node* node){
    if(node) {
        deletefunction(node->leftSubtree());
        deletefunction(node->rightSubtree());
    }
    delete node;
}

BinaryTree::~BinaryTree() {
    // TODO: implement this function.
    deletefunction(root);
}

string findpathhelper(Node *node, const string &s) {
    if (!node) return "-1";
    if (node->getstr() == s) return "";
    if (findpathhelper(node->leftSubtree(), s) != "-1") return "0" + findpathhelper(node->leftSubtree(), s);
    if (findpathhelper(node->rightSubtree(), s) != "-1") return "1" + findpathhelper(node->rightSubtree(), s);
    return "-1";
}

string BinaryTree::findPath(const string &s) const{
    // TODO: implement this function.
    return findpathhelper(root, s);
}

int sumhelper(Node *node) {
    if (!node) return 0;
    else return node->getnum() + sumhelper(node->leftSubtree()) + sumhelper(node->rightSubtree());
}

int BinaryTree::sum() const {
    // TODO: implement this function.
    return sumhelper(root);
}

int depthhelper(Node *node) {
    if (!node) return 0;
    else return (depthhelper(node->leftSubtree()) > depthhelper(node->rightSubtree()))? depthhelper(node->leftSubtree()) + 1: depthhelper(node->rightSubtree()) + 1;
}

int BinaryTree::depth() const {
    // TODO: implement this function.
    return depthhelper(root);
}

void preorderhelper(Node *node) {
    if (node) {
        cout << node->getnum() << " ";
        if (node->leftSubtree()) preorderhelper(node->leftSubtree());
        if (node->rightSubtree()) preorderhelper(node->rightSubtree());
    }
}

void BinaryTree::preorder_num() const {
    // TODO: implement this function.
    preorderhelper(root);
}

void inorderhelper(Node *node) {
    if (node) {
        if (node->leftSubtree()) inorderhelper(node->leftSubtree());
        cout << node->getstr() << " ";
        if (node->rightSubtree()) inorderhelper(node->rightSubtree());
    }
}

void BinaryTree::inorder_str() const {
    // TODO: implement this function.
    inorderhelper(root);
}

void postorderhelper(Node *node) {
    if (node) {
        if (node->leftSubtree()) postorderhelper(node->leftSubtree());
        if (node->rightSubtree()) postorderhelper(node->rightSubtree());
        cout << node->getnum() << " ";
    }
}

void BinaryTree::postorder_num() const {
    // TODO: implement this function.
    postorderhelper(root);
}

bool allPathSumGreaterhelper(Node *node, int temp) {
    if (!node) {
        if (temp < 0) return true;
        else if (temp >= 0) return false;
    }
    else {
        if (!node->leftSubtree() && !node->rightSubtree()) return temp < node->getnum();
        if (!node->leftSubtree()) return allPathSumGreaterhelper(node->rightSubtree(), temp - node->getnum());
        if (!node->rightSubtree()) return allPathSumGreaterhelper(node->leftSubtree(), temp - node->getnum());
        return allPathSumGreaterhelper(node->leftSubtree(), temp - node->getnum()) && allPathSumGreaterhelper(node->rightSubtree(), temp - node->getnum());
    }
    return true;
}

bool BinaryTree::allPathSumGreater(int temp) const {
    // TODO: implement this function.
    return allPathSumGreaterhelper(root, temp);
}

bool compare(Node *thisnode, Node *treenode) {
    if (!treenode) return true;
    if (!thisnode) return false;
    if (thisnode->getnum() == treenode->getnum()) return compare(thisnode->leftSubtree(), treenode->leftSubtree()) && compare(thisnode->rightSubtree(), treenode->rightSubtree());
    else return false;
}

bool coverbyhelper(Node *thisnode, Node *treenode) {
    if (!treenode) return true;
    if (!thisnode) return false;
    if (thisnode->getnum() == treenode->getnum()) return compare(thisnode->leftSubtree(), treenode->leftSubtree()) && compare(thisnode->rightSubtree(), treenode->rightSubtree());
    else return coverbyhelper(thisnode->leftSubtree(), treenode) || coverbyhelper(thisnode->rightSubtree(), treenode);
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    return coverbyhelper(root, tree.root);
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    // TODO: implement this function.
    return coverbyhelper(tree.root, root);
}

Node* copyhelper(Node* node){
    Node* a = new Node(node->getstr(), node->getnum());
    if(!node->leftSubtree()) a->setleft(copyhelper(node->leftSubtree()));
    if(!node->rightSubtree()) a->setright(copyhelper(node->rightSubtree()));
    return a;
}

BinaryTree BinaryTree::copy() const {
    // TODO: implement this function.
    Node* copiednode = copyhelper(root);
    return BinaryTree(copiednode);
}


