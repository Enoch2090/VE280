#include "binaryTree.h"
#include "huffmanTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

int poweroftwo(int m) {
    int a = 1;
    for (int i = 0; i < m; i++) a *= 2;
    return a;
}
int main(int argc, char *argv[]) {
    // TODO: implement this function
    string treefile = argv[1], binaryfile = argv[2], line, allinput, in, value, comma = ",", enter = "\n";
    int number = -1, index = 1, linenumber = 0;
    ifstream ftree, fbinary;
    stringstream input;
    ftree.open(treefile);
    fbinary.open(binaryfile);
    //cout<<ftree.is_open()<<endl<<fbinary.is_open()<<endl;
    while (ftree.peek() != EOF) {
        getline(ftree, line);
        //cout<<line;
        linenumber++;
        allinput += line;
    }
    auto *array = new string[poweroftwo(linenumber)];
    input.str(allinput);
    //cout<<"hahahha"<<allinput<<endl;
    while (input.peek() != EOF) { //will there be an extra at the end of file
        in = input.get();
        //cout<<in;
        if (in == enter) {
            cout<<6666<<endl;
            continue;
        }
        else if (in != comma) value += in;
        else {
            array[++number] = value;
            //cout<<value<<endl;
            value = "";
        }
    }
    while (fbinary.peek() != EOF) {
        fbinary >> in;
        //cout<<in<<" ";
        index = poweroftwo(in.length()) - 1;
        for (int i = 0; i < (int)in.length(); i++) index += poweroftwo((int)in.length() - i - 1) * (int)(in[i] - (int)('0'));
        //cout<<index<<endl;
        if (array[index] == " ") cout << " ";
        else if (array[index] == "\\n") cout << endl;
        else cout << array[index];
    }
    delete[] array;
}