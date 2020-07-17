#include "binaryTree.h"
#include "huffmanTree.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class nullNode
{
};

string decode(Node *root, const string &bincode)
{
    Node *node;
    node = root;
    for (int i = 0; i < bincode.length(); i++)
    {
        if (bincode[i] == '0')
        {
            if (node->leftSubtree() != nullptr)
            {
                node = node->leftSubtree();
            }
            else
            {
                nullNode n;
                throw n;
            }
        }
        else if (bincode[i] == '1')
        {
            if (node->rightSubtree() != nullptr)
            {
                node = node->rightSubtree();
            }
            else
            {
                nullNode n;
                throw n;
            }
        }
    }
    return node->getstr();
}

void decompress(string treefile, string binfile)
{
    HuffmanTree h(treefile);
    //h.printTree();
    ifstream bincode(binfile);
    string binBuffer;
    while (bincode.peek() != EOF)
    {
        getline(bincode, binBuffer, ' ');
        cout << decode(h.root, binBuffer);
    }
    bincode.close();
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return 0;
    }
    else
    {
        string treefile(argv[1]);
        string binfile(argv[2]);
        decompress(treefile, binfile);
    }
    return 0;
}