#include "calculator_mk2.h"
#include "ui_calculator_mk2.h"
#include <QPushButton>
#include <QMessageBox>

#include <stack>
#include <iostream>
#include <sstream>

Calculator_mk2::Calculator_mk2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calculator_mk2)
{
    ui->setupUi(this);


    // добавляем кнопки с цифрами
    for(int i = 0; i <= 9; ++i)
    {
        QPushButton* button = new QPushButton();
        button->setText(QString::number(i));
        QSizePolicy policy = button->sizePolicy();
        policy.setVerticalPolicy(QSizePolicy::Expanding);
        button->setSizePolicy(policy);
        button->setStyleSheet("font-size: 16px;");
        connect(button, &QPushButton::clicked, this, &Calculator_mk2::processInput);
        ui->digitsPanel->addWidget(button, i/3, i%3);
    }

    // связываем кнопки-операторы
    connect(ui->btnDivide, &QPushButton::clicked, this, &Calculator_mk2::processInput);
    connect(ui->btnDot, &QPushButton::clicked, this, &Calculator_mk2::processInput);
    connect(ui->btnMinus, &QPushButton::clicked, this, &Calculator_mk2::processInput);
    connect(ui->btnPlus, &QPushButton::clicked, this, &Calculator_mk2::processInput);
    connect(ui->btnMultiply, &QPushButton::clicked, this, &Calculator_mk2::processInput);
    connect(ui->btnLeftPar, &QPushButton::clicked, this, &Calculator_mk2::processInput);
    connect(ui->btnRightPar, &QPushButton::clicked, this, &Calculator_mk2::processInput);

    connect(ui->btnEquals, &QPushButton::clicked, this, &Calculator_mk2::performCalculation);

}

Calculator_mk2::~Calculator_mk2()
{
    delete ui;
}

void Calculator_mk2::processInput()
{
    ui->inputText->insert(static_cast<QPushButton*>(QObject::sender())->text());
}

void Calculator_mk2::performCalculation()
{
    std::string infix = ui->inputText->text().toStdString();
    if(!checkParenthesis(infix))
    {
        QMessageBox::warning(this, tr("Parenthesis error!"), tr("Error in parenthesis. Please check"));
    }
    else
    {
        std::string postfix = infixToPostfix(infix);
        ui->reverseNotationText->setText(QString::fromStdString(postfix));
        ui->resultText->setText(QString::number(calculatePostfix(postfix)));
    }
}

int Calculator_mk2::precedence(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool Calculator_mk2::checkParenthesis(std::string str)
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

std::string Calculator_mk2::infixToPostfix(std::string infix)
{
    std::stack<char> st;
    std::string postfix = "";
    for (int i = 0; i < infix.length(); i++) {
            char c = infix[i];
            if (isalnum(c))
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
                    && precedence(c)
                    <= precedence(st.top())) {
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

qreal Calculator_mk2::calculatePostfix(std::string str)
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

    for (int i = 0; i < tokens.size(); ++i)
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
            double result = calculate(operand2, operand1, c);
            st.push(result);
        }
    }
    return st.top();
}

qreal Calculator_mk2::calculate(double left, double right, char op)
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
