#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

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
    double ERROR = 1e-8;
    bool isPowerNumber = false;
    if (input_val == 1)
    {
        isPowerNumber = true;
    }
    else
    {
        double sqr = sqrt(input_val);
        if (abs(sqr - double(round(sqr))) <= ERROR) // Most numbers are the squares of something. So if sqrt is an int, it is a power number, therefore quit the following craps.
        {
            isPowerNumber = true;
            return isPowerNumber;
        }

        double cubr = pow(input_val, 1.0 / 3);
        if (abs(cubr - double(round(cubr))) <= ERROR) // Similar to preceding if.
        {
            isPowerNumber = true;
            return isPowerNumber;
        }

        int max_base = sqrt(input_val);
        for (int base = 2; base <= max_base; base++) // If not a square or cube, then search all numbers.
        {
            double power = log(input_val) / log(base);
            if (abs(power - double(round(power))) <= ERROR) // Check if the double variable power represents an "integer". The error can be defined in the header.
            {
                isPowerNumber = true;
            }
            else
            {
                continue;
            }
            break;
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
    ofstream triangle, palindrome, power, abundant;
    triangle.open("triangle_h.txt");
    palindrome.open("palindrome_h.txt");
    power.open("power_h.txt");
    abundant.open("abundant_h.txt");
    if (triangle.fail() || palindrome.fail() || power.fail() || abundant.fail())
    {
        cout << "fail!!!!" << endl;
        exit(1);
    }

    for (int integer = 1; integer <= 10000000; integer++)
    {
        if (isTriangleNumber(integer))
        {
            triangle << integer << endl;
        }
        if (isPalindrome(integer))
        {
            palindrome << integer << endl;
        }
        if (isPowerNumber(integer))
        {
            power << integer << endl;
        }
        if (isAbundantNumber(integer))
        {
            abundant << integer << endl;
        }
    }

    triangle.close();
    palindrome.close();
    power.close();
    abundant.close();

    return 0;
}
