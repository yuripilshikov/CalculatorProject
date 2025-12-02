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

    connect(ui->btnClear, &QPushButton::clicked, this, [this]{
        ui->inputText->clear();
        ui->reverseNotationText->clear();
        ui->resultText->clear();
    });
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
    if(!cmm.CheckParenthesis(infix))
    {
        QMessageBox::warning(this, tr("Parenthesis error!"), tr("Error in parenthesis. Please check"));
    }
    else
    {
        std::string postfix = cmm.InfixToPostfix(infix);
        ui->reverseNotationText->setText(QString::fromStdString(postfix));
        ui->resultText->setText(QString::number(cmm.CalculatePostfix(postfix)));
    }
}


