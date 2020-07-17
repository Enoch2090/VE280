#include <iostream>
using namespace std;
class asciiArray
{
private:
    char ascii[28];
    int freq[28];

public:
    asciiArray()
    {
        char a[28] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\n', ' '};
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

int main()
{
    for (char i = 'a'; i <= 'z'; i++)
    {
        cout << i << endl;
    }
    return 0;
}