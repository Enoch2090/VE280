#include "dlist.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// ----------Utilities----------
char topOfChar(Dlist<char> &operatorStack)
// REQUIRES: operatorStack a Dlist of char
// EFFECTS: return the top of the stack.
{
    if (operatorStack.isEmpty())
    {
        return '\n';
    }
    char *topChar = operatorStack.removeFront();
    operatorStack.insertFront(topChar);
    return *topChar;
}

void popChar(Dlist<char> &operatorStack, ostringstream &os)
// REQUIRES: operatorStack a Dlist of char
// EFFECTS: pop the top of the stack.
{
    char *popedOperator = operatorStack.removeFront();
    char temp = *popedOperator;
    os << temp << " ";
    delete popedOperator;
}

int topOfInt(Dlist<int> &operandStack)
// REQUIRES: operatorStack a Dlist of int
// EFFECTS: return the top of the stack.
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
// REQUIRES: operatorStack a Dlist of int
// EFFECTS: pop the top of the stack.
{
    int *popedOperator = operandStack.removeFront();
    int temp = *popedOperator;
    os << temp << " ";
    delete popedOperator;
}

bool hasGTPrecedence(const char &op1, const char &op2)
// REQUIRES: op1, op2 2 chars of operators
// EFFECTS: check whether op1 has greater precedence.
{
    return ((op2 == '+' || op2 == '-') ? (!(op1 == '+' || op1 == '-')) : (false));
    // (op2 == + or -) => (op1 == + or -) then equal prec, otherwise op1 has gt prec.
    // (op2 != + and -) => op1 can't have gt prec.
}

bool hasEQPrecedence(const char &op1, const char &op2)
// REQUIRES: op1, op2 2 chars of operators
// EFFECTS: check whether they have equal precedence.
{
    return ((op2 == '+' || op2 == '-') ? (op1 == '+' || op1 == '-') : (op1 == '*' || op1 == '/'));
}
// ----------Operations----------

void getVAL(string expression)
// EFFECTS: evaluates the RPN exp and print the value
{
    try
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
                exp.get(); // Clean possible spaces
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
    catch (emptyList e)
    {
        throw e;
    }
}

void getRPN()
// EFFECTS: get the RPN string and call getVAL()
{
    try
    {
        string input = "";
        getline(cin, input);
        istringstream is;
        ostringstream os;
        is.str(input);
        string peeked;
        int currOperand = 0;
        char currOperator;
        Dlist<char> operatorStack;
        bool emptyIn = true;
        int lParenthesis = 0;
        int rParenthesis = 0;
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
                    lParenthesis++; // lP must match with rP at the end
                }
                else if (currOperator == ')')
                {
                    rParenthesis++;
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
            emptyIn = false;
        }
        while (!operatorStack.isEmpty())
        {
            popChar(operatorStack, os);
        }
        if (lParenthesis != rParenthesis)
        {
            cout << "ERROR: Parenthesis mismatch" << endl; // Deal with more lParenthesis
            return;
        }
        if (emptyIn)
        {
            cout << "ERROR: Not enough operands" << endl;
            return;
        }
        cout << os.str() << endl;
        getVAL(os.str());
    }
    catch (emptyList e)
    {
        throw e;
    }
}

int main()
{
    try
    {
        getRPN();
    }
    catch (emptyList e)
    {
        return 0;
    }
    return 0;
}