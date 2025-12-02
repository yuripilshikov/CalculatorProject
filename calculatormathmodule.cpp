#include "calculatormathmodule.h"
#include <stack>
#include <sstream>
#include <vector>

int CalculatorMathModule::Precedence(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double CalculatorMathModule::Calculate(double left, double right, char op)
{
    switch(op)
    {
        case u'+': return left + right;
        case u'-': return left - right;
        case u'*': return left * right;
        case u'/': return left / right;
        default: return 0;
    }
}

bool CalculatorMathModule::CheckParenthesis(std::string str)
{
    std::stack<char> st;
    for (int i = 0; i < str.length(); ++i)
    {
        char c = str[i];
        switch (c)
        {
        case '(':
            st.push(c);
            break;
        case ')':
            if (st.empty() || st.top() != '(') return false;
            st.pop();
            break;
        }
    }
    if (!st.empty()) return false;
    return true;
}

std::string CalculatorMathModule::InfixToPostfix(std::string infix)
{
    std::stack<char> st;
    std::string postfix = "";
    for (unsigned int i = 0; i < infix.length(); i++) {
            char c = infix[i];
            if (isalnum(c) || c == '.')
            {
                postfix += c;
            }
            else if (c == '(')
            {
                st.push('(');
            }
            else if (c == ')') {
                postfix += ' ';
                while (st.top() != '(') {
                    postfix += st.top();
                    st.pop();
                }
                st.pop();
            }
            else {
                postfix += ' ';
                while (!st.empty()
                    && Precedence(c)
                    <= Precedence(st.top())) {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                st.push(c);
            }
        }
        while (!st.empty()) {
            postfix += ' ';
            postfix += st.top();
            st.pop();
        }

        return postfix;
}

double CalculatorMathModule::CalculatePostfix(std::string str)
{
    // tokenize first
    char delimeter = ' ';

    std::istringstream stream(str);
    std::vector<std::string> tokens;
    std::string token;
    while (getline(stream, token, delimeter))
    {
        tokens.push_back(token);
    }

    std::stack<double> st;

    for (unsigned int i = 0; i < tokens.size(); ++i)
    {
        char c = tokens[i][0];

        if (std::isdigit(c))
        {
            st.push(std::stod(tokens[i]));
        }
        else
        {
            double operand1 = st.top();
            st.pop();
            double operand2 = st.top();
            st.pop();
            double result = Calculate(operand2, operand1, c);
            st.push(result);
        }
    }
    return st.top();
}
