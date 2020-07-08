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
        this->children[child_index] = NULL;
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
    if (this->child_num == sub->child_num && this->value == sub->value)
    {
        bool level_equal = true;
        for (int index = 0; index < this->child_num && level_equal; index++)
        {
            level_equal = level_equal && this->children[index]->contain(sub->children[index]);
        }
        return level_equal;
    }
    else
    {
        bool sublevel_equal = false;
        for (int index = 0; index < this->child_num; index++)
        {
            sublevel_equal = sublevel_equal || this->children[index]->contain(sub);
        }
        return sublevel_equal;
    }
}

int Node::getHeight()
{
    if (this->child_num == 0)
    {
        this->height = 0;
        return 0;
    }
    else
    {
        int max_height = -1;
        int child_height = -1;
        for (int index = 0; index < this->child_num; index++)
        {
            child_height = this->children[index]->getHeight();
            if (child_height > max_height)
            {
                max_height = child_height;
            }
        }

        this->height = max_height + 1;
        return (max_height + 1);
    }
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