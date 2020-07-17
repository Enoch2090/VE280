#include "binaryTree.h"
#include "huffmanTree.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    // TODO: implement this function
    string filename, input, space = " ", enter = "\n", allinput;
    string letter[26] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    int leng, charnum = 28, flag = 0, all = 0;
    Node *array[56] = {};
    Node *exchange;
    for (int i = 0; i < 26; i++) array[i] = new Node(letter[i], 0);
    array[26] = new Node(" ", 0);
    array[27] = new Node("\n",0);
    if (argc == 2) filename = argv[1];
    else filename = argv[2];
    ifstream fin;
    fin.open(filename);
    //cout<<fin.is_open();
    while (getline(fin, input)){
        allinput += input; allinput += "\n";
        //cout<<input;
        leng = input.length();
        for (int i = 0; i < leng; i++) {
            if (input[i] == ' ') array[26]->incnum();
            else array[(int)(input[i] - (int)('a'))]->incnum();
        }
        array[27]->incnum();
    }
    //cout<<endl;
    //for (int i = 0; i < 28; i++) cout<<array[i]->getnum()<< " ";
    //cout<<endl;
    while (charnum > 1) {
        //for (int i = 0; i < 28; i++) cout<<array[i]->getnum()<< " ";cout<<endl;
        for (int i = 0; i < charnum; i++) {
            for (int j = i + 1; j < charnum; j++) {
                if (array[j]->getnum() > array[i]->getnum() || (array[j]->getnum() == array[i]->getnum() && array[j]->getstr()[0] > array[i]->getstr()[0])) {
                    exchange = array[i];
                    array[i] = array[j];
                    array[j] = exchange;
                }
            }
        }
        if (!flag) {
            flag = 1; charnum = 0; all = 0;
            for (int i = 0; i < 28; i++) {
                if (array[i]->getnum() != 0) {
                    charnum++;
                    all++;
                }
            }
        }
        //cout<< charnum<<" "<<all<<endl;
        //for (int i = 0; i < 28; i++) cout<<array[i]->getnum()<< " ";cout<<endl;
        exchange = exchange->mergeNodes(array[charnum - 2], array[charnum - 1]);
        for (int i = all - 1; i >= charnum - 2; i--) array[i + 1] = array[i];
        //for (int i = 0; i < 28; i++) cout<<array[i]->getnum()<< " ";cout<<endl;
        exchange->setleft(array[charnum - 1]);
        exchange->setright(array[charnum]);
        array[charnum - 2] = exchange;
        charnum--;
        all++;
    }
    HuffmanTree a = HuffmanTree(array[0]);
    if (argc == 3) a.printTree();
    if (argc == 2) {
        for (char i : allinput) {
            if (i == ' ') cout << a.findPath(" ") << " ";
            else if (i == '\n') cout << a.findPath("\n") << " ";
            else cout << a.findPath(letter[(int)i - (int)'a']) << " ";
        }
    }
    return 0;
}