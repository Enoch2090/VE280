#include "dlist.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// ----------Utilities----------
char topOfChar(Dlist<char> &operatorStack)
{
    if (operatorStack.isEmpty())
    {
        return 'N';
    }
    char *topChar = operatorStack.removeFront();
    operatorStack.insertFront(topChar);
    return *topChar;
}

void popChar(Dlist<char> &operatorStack, ostringstream &os)
{
    char *popedOperator = operatorStack.removeFront();
    char temp = *popedOperator;
    os << temp << " ";
    delete popedOperator;
}

int topOfInt(Dlist<int> &operandStack)
{
    if (operandStack.isEmpty())
    {
        return -1;
    }
    int *topInt = operandStack.removeFront();
    operandStack.insertFront(topInt);
    return *topInt;
}

void popInt(Dlist<int> &operandStack, ostringstream &os)
{
    int *popedOperator = operandStack.removeFront();
    int temp = *popedOperator;
    os << temp << " ";
    delete popedOperator;
}

bool hasGTPrecedence(const char &op1, const char &op2)
{
    return ((op2 == '+' || op2 == '-') ? (!(op1 == '+' || op1 == '-')) : (false));
    // (op2 == + or -) => (op1 == + or -) then equal prec, otherwise op1 has gt prec.
    // (op2 != + and -) => op1 can't have gt prec.
}

bool hasEQPrecedence(const char &op1, const char &op2)
{
    return ((op2 == '+' || op2 == '-') ? (op1 == '+' || op1 == '-') : (op1 == '*' || op1 == '/'));
}
// ----------Operations----------

void getVAL(string expression)
{
    istringstream exp;
    exp.str(expression);
    string peeked;
    int currOperand;
    char currOperator;
    Dlist<int> operandStack;
    while (exp.peek() != EOF)
    {
        peeked = exp.peek();
        if (peeked != "+" && peeked != "-" && peeked != "*" && peeked != "/" && peeked != "(" && peeked != ")" && peeked != " ")
        {
            exp >> currOperand;
            exp.get();
            int *newOperand = new int(currOperand);
            operandStack.insertFront(newOperand);
        }
        else if (peeked == " ")
        {
            exp.get();
        }
        else
        {
            exp >> currOperator;
            exp.get();
            if (operandStack.isEmpty())
            {
                cout << "ERROR: Not enough operands" << endl;
                return;
            }
            int *operand1 = operandStack.removeFront();
            if (operandStack.isEmpty())
            {
                cout << "ERROR: Not enough operands" << endl;
                delete operand1;
                return;
            }
            int *operand2 = operandStack.removeFront();
            int res = 0;
            if (currOperator == '+')
            {
                res = (*operand1) + (*operand2);
            }
            else if (currOperator == '-')
            {
                res = (*operand2) - (*operand1);
            }
            else if (currOperator == '*')
            {
                res = (*operand1) * (*operand2);
            }
            else if (currOperator == '/')
            {
                if ((*operand1) == 0)
                {
                    cout << "ERROR: Divide by zero" << endl;
                    delete operand1;
                    delete operand2;
                    return;
                }
                res = (*operand2) / (*operand1);
            }
            delete operand1;
            delete operand2;
            int *result = new int(0);
            *result = res;
            operandStack.insertFront(result);
        }
    }
    int *finalResult = operandStack.removeFront();
    if (!operandStack.isEmpty())
    {
        cout << "ERROR: Too many operands" << endl;
        delete finalResult;
        return;
    }
    cout << *finalResult << endl;
    delete finalResult;
}

void getRPN()
{
    string input = "";
    getline(cin, input);
    istringstream is;
    ostringstream os;
    is.str(input);
    string peeked;
    int currOperand;
    char currOperator;
    Dlist<char> operatorStack;
    while (is.peek() != EOF)
    {
        peeked = is.peek();
        if (peeked != "+" && peeked != "-" && peeked != "*" && peeked != "/" && peeked != "(" && peeked != ")" && peeked != " ")
        {
            // Not operators, then it's a operand.
            is >> currOperand;
            is.get();
            os << currOperand << " ";
            //cout << currOperand << " isNUM" << endl;
        }
        else if (peeked == " ")
        {

            is.get();
        }
        else // An operator
        {
            is >> currOperator;
            is.get();
            //cout << currOperator << " isOP" << endl;
            if (currOperator != '(' && currOperator != ')')
            {
                while ((!operatorStack.isEmpty()) ? ((((hasGTPrecedence(topOfChar(operatorStack), currOperator)) || (hasEQPrecedence(topOfChar(operatorStack), currOperator))) && topOfChar(operatorStack) != '(')) : false)
                {
                    popChar(operatorStack, os);
                }
                char *newOperator = new char;
                *newOperator = currOperator;
                operatorStack.insertFront(newOperator);
            }
            else if (currOperator == '(')
            {
                char *newOperator = new char;
                *newOperator = currOperator;
                operatorStack.insertFront(newOperator);
            }
            else if (currOperator == ')')
            {
                while ((!operatorStack.isEmpty()) ? topOfChar(operatorStack) != '(' : false)
                {
                    popChar(operatorStack, os);
                }
                if ((!operatorStack.isEmpty()) ? topOfChar(operatorStack) == '(' : false)
                {
                    char *popedOperator = operatorStack.removeFront();
                    delete popedOperator;
                }
                else
                {
                    cout << "ERROR: Parenthesis mismatch" << endl;
                    return;
                }
            }
        }
        // if (!operatorStack.isEmpty())
        // {
        //     cout << topOfChar(operatorStack) << endl;
        // }
    }
    while (!operatorStack.isEmpty())
    {
        popChar(operatorStack, os);
    }
    cout << os.str() << endl;
    getVAL(os.str());
}

int main()
{
    getRPN();
    return 0;
}