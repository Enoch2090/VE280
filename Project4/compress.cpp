#include "binaryTree.h"
#include "huffmanTree.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class asciiArray
{
private:
    char ascii[28];
    int freq[28];

public:
    asciiArray()
    {
        char a[28] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\n', ' '};
        for (int i = 0; i < 28; i++)
        {
            this->ascii[i] = a[i];
            this->freq[i] = 0;
        }
    }
    int operator[](char c)
    {
        for (int i = 0; i < 28; i++)
        {
            if (ascii[i] == c)
            {
                return freq[i];
            }
        }
        return -1;
    }
    void addFreq(char c)
    {
        for (int i = 0; i < 28; i++)
        {
            if (ascii[i] == c)
            {
                freq[i]++;
            }
        }
    }
};

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
    string code;
    asciiArray arr;
    char c;
    ifstream file(filename);
    vector<Node *> nodes;
    Node *merged_node;

    while (file.peek() != EOF)
    {
        file.get(c);
        arr.addFreq(c);
    }
    for (char i = 'a'; i <= 'z'; i++)
    {
        if (arr[i] != 0)
        {
            string ascii_char = string(1, i);
            Node *new_node = new Node(ascii_char, arr[i]);
            nodes.push_back(new_node); // Convert the array to Nodes.
        }
    }
    if (arr['\n'] != 0)
    {
        string ascii_char = string(1, '\n');
        Node *new_node = new Node(ascii_char, arr['\n']);
        nodes.push_back(new_node);
    }
    if (arr[' '] != 0)
    {
        string ascii_char = string(1, ' ');
        Node *new_node = new Node(ascii_char, arr[' ']);
        nodes.push_back(new_node);
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
            code = h.findPath(string(1, c));
            cout << code << " ";
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc == 3 && string(argv[1]) == "-tree")
    {
        compress(true, argv[2]);
    }
    else if (argc == 2)
    {
        compress(false, argv[1]);
    }
}