#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    istringstream is;
    string temp;
    getline(cin, temp);
    is.str(temp);
    string fuck;
    is >> fuck;
    is.get();
    cout << fuck << endl;
    cout << (char)is.peek() << endl;
    return 0;
}