#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
    string in;
    getline(cin, in);
    replace(in.begin(), in.end(), ',', ' ');
    string name;
    istringstream iStream;
    iStream.str(in);
    int i = 0;
    while (iStream >> name)
    {
        cout << name << endl;
        i++;
    }
    cout << i << endl;
    return 0;
}