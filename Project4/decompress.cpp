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
void throwNullNNode()
// EFFECTS: Throw an instance of nullNode(under very rare circumstances).
{
    nullNode n;
    throw n;
}

string decode(Node *root, const string &bincode)
// REQUIRES: root the root of a huffman tree, bincode the encoded code of a character.
// EFFECTS: returns the decoded character.
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
                throwNullNNode();
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
                throwNullNNode();
            }
        }
    }
    return node->getstr();
}

void decompress(string treefile, string binfile)
// REQUIRES: treefile the path to tree, binfile the path to the encoded file.
// EFFECTS: prints the decoded string.
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