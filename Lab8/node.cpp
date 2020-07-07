#include "node.h"
#include <iostream>
using namespace std;

Node::Node(int _value, int _n)
{
    this->value = _value;
    this->child_num = 0;
    this->n = _n;
    this->children = new Node *[_n];
    for (int child_index = 0; child_index < _n; child_index++)
    {
        this->children[child_index] = nullptr;
    }
    this->parent = NULL;
    this->height = 0;
}

Node::~Node()
{
    for (int child_index = 0; child_index < this->n; child_index++)
    {
        delete this->children[child_index];
    }
    delete[] this->children;
}

void Node::addChild(int _value)
{
    if (this->child_num < this->n)
    {
        Node *child = new Node(_value, this->n);
        child->child_num = 0;
        child->value = _value;
        child->n = this->n;
        child->height = 0;
        child->parent = this;
        addChild(child);
    }
    else
    {
        tooManyChildren t;
        throw t;
    }
}

void Node::addChild(Node *child)
{

    this->children[child_num] = child;
    int max_height = 0;
    for (int index = 0; index < this->child_num; index++)
    {
        if (this->children[index]->height >= max_height)
        {
            max_height = height;
        }
    }
    this->height = max_height + 1;
    Node *parent = this->parent;
    while (parent != NULL) // Update height
    {
        int max_height = 0;
        for (int index = 0; index < parent->child_num; index++)
        {
            if (parent->children[index]->height >= max_height)
            {
                max_height = height;
            }
        }
        parent->height = (max_height + 1);
        parent = parent->parent;
    }
    this->child_num++;
}

void Node::traverse()
{
    cout << this->value << " ";
    for (int index = 0; index < this->child_num; index++)
    {
        this->children[index]->traverse();
    }
}

bool Node::contain(Node *sub)
{
    if (sub == this)
    {
        return true;
    }
    else
    {
        for (int child_index = 0; child_index < this->child_num; child_index++)
        {
            if (this->children[child_index]->contain(sub))
            {
                return true;
            }
        }
    }
    return false;
}

int Node::getHeight()
{
    return this->height;
}

Node &Node::operator[](int i)
{
    if (i >= this->child_num)
    {
        invalidIndex i;
        throw i;
    }
    else
    {
        return *(this->children[i]);
    }
}