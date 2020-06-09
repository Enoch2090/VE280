#include <iostream>
#include <string>
using namespace std;

int add(int count, int arr[])
{
    int ans = 0;
    for (int i = 0; i < count; i++)
    {
        ans += arr[i];
    }
    return ans;
}

int small(int count, int arr[])
{
    int ans = 2147483647;
    for (int i = 0; i < count; i++)
    {
        if (arr[i] < ans)
        {
            ans = arr[i];
        }
    }
    return ans;
}

int main(int argc, char *argv[])
{
    bool doHelp = false;
    bool doAdd = false;
    bool doSmall = false;
    bool isVerbose = false;
    bool readSmallIn = false;
    int smallIn = 0;
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "--help")
        {
            doHelp = true;
        }
        else if (string(argv[i]) == "--add")
        {
            doAdd = true;
        }
        else if (string(argv[i]) == "--small")
        {
            doSmall = true;
            readSmallIn = true;
        }
        else if (string(argv[i]) == "--verbose")
        {
            isVerbose = true;
        }
        else
        {
            if (readSmallIn)
            {
                smallIn = atoi(argv[i]);
                readSmallIn = false;
            }
        }
    }

    if (doHelp)
    {
        cout << "Hey, I love Integers." << endl;
    }
    if (doAdd)
    {
        int count;
        cin >> count;
        int arr[count];
        for (int i = 0; i < count; i++)
        {
            cin >> arr[i];
        }
        if (isVerbose)
        {
            cout << "This is add operation." << endl;
        }
        cout << add(count, arr) << endl;
    }
    if (doSmall)
    {
        int count;
        cin >> count;
        int arr[count];
        for (int i = 0; i < count; i++)
        {
            cin >> arr[i];
        }
        if (isVerbose)
        {
            cout << "This is small operation." << endl;
        }
        cout << small(count, arr) + smallIn << endl;
    }
    if (!doHelp && !doAdd && !doSmall)
    {
        cout << "No work to do!" << endl;
    }
    return 0;
}