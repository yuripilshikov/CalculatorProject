#ifndef CALCULATOR_MK2_H
#define CALCULATOR_MK2_H

#include <QWidget>

namespace Ui {
class Calculator_mk2;
}

class Calculator_mk2 : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator_mk2(QWidget *parent = nullptr);
    ~Calculator_mk2();

public slots:
    void processInput();
    void performCalculation();

private:
    Ui::Calculator_mk2 *ui;

    int precedence(char op);
    bool checkParenthesis(std::string str);
    std::string infixToPostfix(std::string str);
    double calculatePostfix(std::string str);
    double calculate(double left, double right, char op);
};

#endif // CALCULATOR_MK2_H
