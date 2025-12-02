#ifndef CALCULATORMATHMODULE_H
#define CALCULATORMATHMODULE_H

#include <string>

class CalculatorMathModule
{
    int Precedence(char op);
    double Calculate(double left, double right, char op);
public:    
    bool CheckParenthesis(std::string str);
    std::string InfixToPostfix(std::string str);
    double CalculatePostfix(std::string str);
};

#endif // CALCULATORMATHMODULE_H
