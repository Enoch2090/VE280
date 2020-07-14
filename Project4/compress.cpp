#include "binaryTree.h"
#include "huffmanTree.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(const Node *n1, const Node *n2) // TODO: CONST POINTER
{
    if (n1->getnum() == n2->getnum())
    {
        return (n1->getstr() < n2->getstr());
    }
    else
    {
        return (n1->getnum() < n2->getnum());
    }
}

void print_node(Node *Node)
{
    cout << Node->getnum() << " " << Node->getstr() << endl;
    if (Node->leftSubtree() != nullptr)
    {
        print_node(Node->leftSubtree());
    }
    if (Node->rightSubtree() != nullptr)
    {
        print_node(Node->rightSubtree());
    }
}

void compress(bool tree, char *filename)
{
    string fname = string(filename);
    string ascii_char;
    string code;
    ifstream file(filename);
    char c;
    int identifier;
    int ascii[128];
    vector<Node *> nodes;
    Node *merged_node;

    for (int i = 0; i < 128; i++)
    {
        ascii[i] = 0; // Init ASCII array
    }
    while (file.peek() != EOF)
    {
        file.get(c);
        identifier = (int)c;
        ascii[identifier]++; // Fill the ASCII array with frequencies.
    }
    for (int i = 0; i < 128; i++)
    {
        if (ascii[i] != 0)
        {
            c = (char)i;
            ascii_char = c;
            Node *new_node = new Node(ascii_char, ascii[i]);
            nodes.push_back(new_node); // Convert the array to Nodes.
        }
    }
    while (nodes.size() > 1)
    {
        sort(nodes.begin(), nodes.end(), compare);
        merged_node = Node::mergeNodes(nodes[1], nodes[0]);
        nodes[0] = nullptr;
        nodes[1] = nullptr;
        nodes.erase(nodes.begin());
        nodes.erase(nodes.begin());
        nodes.push_back(merged_node);
    }
    file.clear();
    file.seekg(0, ios::beg);
    HuffmanTree h(nodes[0]);
    nodes[0] = nullptr;
    if (tree)
    {
        h.printTree();
    }
    else
    {
        while (file.peek() != EOF)
        {
            file.get(c);
            code = h.findPath(string(&c));
            cout << code << " ";
        }
    }
}

int main(int argc, char *argv[])
{
    bool tree = false;
    if (argc == 2 && string(argv[1]) == "-tree")
    {
        tree = true;
    }
    if (argc >= 2)
    {
        compress(tree, argv[argc - 1]);
    }
}