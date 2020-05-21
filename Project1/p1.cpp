#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#define ERROR 1e-10
using namespace std;

bool isTriangleNumber(int input_val)
{
    int n = floor(sqrt(2 * input_val)); // If n exists, it should be close to the sqrt here.
    bool isTriangleNumber = (input_val == n * (n + 1) / 2);
    return isTriangleNumber;
}

bool isPalindrome(int input_val)
{
    string input_str = to_string(input_val);

    string reversed_str = string(input_str);
    int len = input_str.length();
    for (int i = 0; i < len; i++)
    {
        reversed_str[i] = input_str[len - i - 1];
    }
    // If the reversed string equals the original string then the input is a palindrome.
    bool isPalindrome = (input_str == reversed_str);
    return isPalindrome;
}

bool isPowerNumber(int input_val)
{
    int max_base = floor(sqrt(input_val));
    bool isPowerNumber = false;
    for (int base = 2; base < max_base + 1; base++)
    {
        double power = log(input_val) / log(base);
        if (power - double(round(power)) <= ERROR) // Check if the double variable power represents an "integer". The error can be defined in the header.
        {
            isPowerNumber = true;
        }
    }
    return isPowerNumber;
}

bool isAbundantNumber(int input_val)
{
    int divisor_sum = 1;
    int max_divisor = floor(input_val / 2) + 1; // Plus one so there is a buffer zone incase input/2 is omitted.
    for (int divisor = 2; divisor < max_divisor; divisor++)
    {
        if (input_val % divisor == 0)
        {
            divisor_sum += divisor;
        }
    }
    bool isAbundantNumber = divisor_sum > input_val;
    return isAbundantNumber;
}

int main()
{
    int input_val = 0;
    int mode_val = 0;
    bool out;
    while (!(input_val > 0 && input_val <= 10000000 && mode_val >= 1 && mode_val <= 4))
    {
        cout << "Please enter the integer and the test number: " << endl;
        cin >> input_val >> mode_val;
    }
    switch (mode_val)
    {
    case 1:
    {
        out = isTriangleNumber(input_val);
        break;
    }
    case 2:
    {
        out = isPalindrome(input_val);
        break;
    }
    case 3:
    {
        out = isPowerNumber(input_val);
        break;
    }
    case 4:
    {
        out = isAbundantNumber(input_val);
        break;
    };
    default:
    {
        out = false;
        break;
    }
    }
    cout << out << endl;
    return 0;
}